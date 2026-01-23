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
- 
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
unsigned long lastUpdate = 0;
unsigned long lastLog = 0;
unsigned long DHTCLOCK = 3500;
unsigned long CLOCK = 2000;
unsigned long LOGCLOCK = 600000; //5 min interval test
const int chipSelect = 4;
unsigned long now;
RTCTime currentTime;
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
  lastUpdate = now;
  lastLog = now;


}

void loop() 
{
  RTC.getTime(currentTime);
  now = millis();

//Log data every 5 mins
  if(now - lastLog >= LOGCLOCK)
  {
    //Non-blocking delay between DHT capture and other sensors
    if(now - lastDHT >= DHTCLOCK)
    {
      lastDHT = now;
      Serial.println("Collecting DHT");
      collectDHT(dht, currentWeather);
    }


    if(now - lastUpdate >= CLOCK)
    {
      lastUpdate = now;
      Serial.println("Collecting BMP");
      collectBMP(bmp280, currentWeather);
      Serial.println("Collecting Date");
      collectDateTime(currentWeather, currentTime);
      Serial.println("Displaying");
      displayToScreen(display, currentWeather);
    }

    lastLog = now;
    Serial.println("Logging Data");
    logWeatherData(currentWeather);
  }

}
