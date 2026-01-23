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
unsigned long lastDHT = 0;
unsigned long lastLog = 0;
unsigned long LOGCLOCK = 300000; //5 min interval test
const int chipSelect = 4;
unsigned long now;
RTCTime currentTime;

enum SampleState
{
  IDLE,
  DHT_COLLECTED,
  COMPLETE
};
SampleState sampleState = SampleState::IDLE;
//--------------------------------------------------------------------
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(SERIALPORT);
  Wire.begin();
  delay(50); //Gives time for I2C to initialise
  startDisplay(display);
  dht.begin();
  if(!bmp280.init(BMDADDR))
  {
    Serial.println("Pressure Sensor Error");
  }
  initialiseSD(chipSelect);
  RTC.begin();

  //Start hard-coded time
  RTCTime startTime(8, Month::DECEMBER, 2025, 11, 50, 0, DayOfWeek::MONDAY, SaveLight::SAVING_TIME_INACTIVE);
  RTC.setTime(startTime);

  
  //Initial collection of sensor information, display, and log sensor data
  RTC.getTime(currentTime);
  now = millis();
  collectDHT(dht, currentWeather);
  collectBMP(bmp280, currentWeather);
  collectDateTime(currentWeather, currentTime);
  displayToScreen(display, currentWeather);
  logWeatherData(currentWeather);

  lastDHT = now;
  lastLog = now;
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
    lastDHT = now;
    sampleState = SampleState::DHT_COLLECTED;
  }


  if(sampleState == SampleState::DHT_COLLECTED)
  {
    Serial.println("Collecting Other Data & Displaying");
    collectBMP(bmp280, currentWeather);
    collectDateTime(currentWeather, currentTime);
    displayToScreen(display, currentWeather);
    sampleState = SampleState::COMPLETE;
  }

  if(sampleState == SampleState::COMPLETE)
  {
    Serial.println("Logging to SD Card");
    logWeatherData(currentWeather);
    lastLog = now;
    sampleState = SampleState::IDLE;
  }
  

}
