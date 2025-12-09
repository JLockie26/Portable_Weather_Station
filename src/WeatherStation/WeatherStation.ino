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
*/
//--------------------------------------------------------------------
#include <Wire.h>
#include <U8g2lib.h>
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
#define DHTPIN 2 //Digital Pin DHT Sensor is connected to
#define DHTTYPE DHT11 //Type of DHT sensor being used
#define BMDADDR 0x77 //I2C address of BMP sensor
#define DHTCLOCK 3000 //Clock timer for DHT-related functions(ms)
#define CLOCK 2000 //Standard clock timer(ms)
#define LOGCLOCK 600000 //Data logging clock timer (10 min intervals in ms)
//--------------------------------------------------------------------
U8G2_SSD1306_128X64_ALT0_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Type of Oled Screen, if you are using a different screen, reference U8g2 library for your screen and replace this variable
DHT dht(DHTPIN, DHTTYPE);
BMP280 bmp280;
WeatherRecord currentWeather;
unsigned long lastDHT = 0;
unsigned long lastUpdate = 0;
const int chipSelect = 4;
//--------------------------------------------------------------------
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(SERIALPORT);
  Wire.begin();
  Wire1.begin();
  delay(50); //Gives time for I2C to initialise
  dht.begin();
  if(!bmp280.init(BMDADDR))
  {
    Serial.println("Pressure Sensor Error");
  }
  initialiseSD(chipSelect);
  display.begin();
  RTC.begin();

  //Start hard-coded time
  RTCTime startTime(8, Month::DECEMBER, 2025, 12, 0, 0, DayOfWeek::MONDAY, SaveLight::SAVING_TIME_INACTIVE);
  RTC.setTime(startTime);

}

void loop() 
{
  unsigned long now = millis();
  RTCTime currentTime;

  RTC.getTime(currentTime);

  //Clock timing to ensure that DHT read timing isnt interrupted by other function calls
  if(now - lastDHT >= DHTCLOCK)
  {
    lastDHT = now;
    collectDHT(dht, currentWeather);
    collectDateTime(currentWeather, currentTime);
  }
  
  if(now - lastUpdate >= CLOCK)
  {
    lastUpdate = now;
    collectBMP(bmp280, currentWeather);
    displayToScreen(display, currentWeather);
  }

  if(now - lastUpdate >= LOGCLOCK)
  {

    //Log Data to SD card

  }
  
}
