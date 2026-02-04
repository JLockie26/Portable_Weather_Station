/*
Author: Jordan Locke
Version: 1.0

The main function/sketch for the portable weather station project. 
This project is intended as an extension of a university assignment and a personal challenge to hone programming skills and learn electronics.
The purpose of this sketch is to initialise all pins and sensors connected to the Arduino before calling separate-
C++ modules to collect, store, and display weather data.

Author: Jordan Locke
Version: 1.1
- Modularised functions for collecting and displaying weather data

Author: Jordan Locke
Version: 1.2
- Implemented SD card writing functionality

Author: Jordan Locke
Version 1.3
- Changed graphics library so OLED screen isn't hogging Serial Data Line
- Modified main logic so weather is only being collected, displayed, and logged every 5 mins (will be changed to 10 mins eventually).
*/
//--------------------------------------------------------------------
#include <Wire.h>
#include <U8x8lib.h>
#include <DHT.h>
#include <Seeed_BMP280.h>
#include <SD.h>
//--------------------------------------------------------------------
#include "WeatherStruct.h"
#include "SensorCollection.h"
#include "DisplayToScreen.h"
#include "SensorLogging.h"
#include "RTC.h"
//--------------------------------------------------------------------
#define SERIALPORT 9600 //Port number Arduino communicates to PC via serial
#define DHTTYPE DHT11 //Type of DHT sensor being used
#define DHTPIN 2 //Digital Pin DHT Sensor is connected to
#define BMDADDR 0x77 //I2C address of BMP sensor
#define _PIN_SDA SDA
#define _PIN_SCL SCL
#define Oled_Screen U8X8_SSD1306_128X64_NONAME_HW_I2C
//--------------------------------------------------------------------
Oled_Screen display(_PIN_SCL, _PIN_SDA, U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);
BMP280 bmp280;
WeatherRecord currentWeather;
unsigned long lastLog = 0;
const unsigned long LOGCLOCK = 300000; //5 min interval test
const unsigned long STATE_DELAY = 20;
static unsigned long stateTimeStamp = 0;
const int chipSelect = 4;
unsigned long now;
int lastTemp, lastHumid = 0;
float lastPress = 0.0f;
RTCTime currentTime;

enum SampleState
{
  IDLE,
  DHT_COLLECTED,
  BMP_COLLECTED,
  BUS_IDLE,
  DISPLAY_COMPLETED,
  COMPLETE
};
SampleState sampleState = SampleState::IDLE;
//--------------------------------------------------------------------
void setup() 
{
  //Initialise all components
  Serial.begin(SERIALPORT);
  Wire.begin();
  delay(50); //Gives time for I2C to initialise
  dht.begin();
  if(!bmp280.init(BMDADDR))
  {
    Serial.println("Pressure Sensor Error");
  }
  initialiseSD(chipSelect);
  //startDisplay(display);
  RTC.begin();

  //Start hard-coded time
  RTCTime startTime(28, Month::JANUARY, 2025, 12, 0, 0, DayOfWeek::SATURDAY, SaveLight::SAVING_TIME_INACTIVE);
  RTC.setTime(startTime);

  //Begin initial log
  lastLog = millis() - LOGCLOCK;
  sampleState = SampleState::IDLE;
}

void loop() 
{
  RTC.getTime(currentTime);
  now = millis();
  

  //Non-blocking delay between DHT capture and other sensors
  if(sampleState == SampleState::IDLE && now - lastLog >= LOGCLOCK)
  {
    Serial.println("Collecting DHT");
    collectDHT(dht, currentWeather);
    stateTimeStamp = now;
    sampleState = SampleState::DHT_COLLECTED;
  }


  else if(sampleState == SampleState::DHT_COLLECTED && now - stateTimeStamp >= STATE_DELAY)
  {
    Serial.println("Collecting BMP");
    collectBMP(bmp280, currentWeather);
    stateTimeStamp = now;
    sampleState = SampleState::BMP_COLLECTED;
  }

  else if(sampleState == SampleState::BMP_COLLECTED && now - stateTimeStamp >= STATE_DELAY)
  {
    sampleState = SampleState::BUS_IDLE;
    stateTimeStamp = now;
  }

  else if(sampleState == SampleState::BUS_IDLE && now - stateTimeStamp >= STATE_DELAY)
  {
    /*
    //Only update the measurements that change (should avoid sending too much data over SDA hopefully)
    if(currentWeather.ambAirTemp != lastTemp)
    {
      Serial.println("Updating Temp");
      updateTemp(display, currentWeather.ambAirTemp);
      lastTemp = currentWeather.ambAirTemp;
    }
      
    
    if(currentWeather.humidity != lastHumid)
    {
      Serial.println("Updating Humid");
      updateHumid(display, currentWeather.humidity);
      lastHumid = currentWeather.humidity;
    }
      

    if(fabs(currentWeather.pressureHpa - lastPress) > 0.1f)
    {
      Serial.println("Updating Press");
      updatePress(display, currentWeather.pressureHpa);
      lastPress = currentWeather.pressureHpa;
    }
    */
    displayToConsole(currentWeather);
      
    stateTimeStamp = now;
    sampleState = SampleState::DISPLAY_COMPLETED;
  }

  else if(sampleState == SampleState::DISPLAY_COMPLETED && now - stateTimeStamp >= STATE_DELAY)
  {
    Serial.println("Logging Time");
    collectDateTime(currentWeather, currentTime);
    stateTimeStamp = now;
    sampleState = SampleState::COMPLETE;
  }

  else if(sampleState == SampleState::COMPLETE && now - stateTimeStamp >= STATE_DELAY)
  {
    Serial.println("Logging to SD Card");
    logWeatherData(currentWeather);
    lastLog = now;
    sampleState = SampleState::IDLE;
  }
}
