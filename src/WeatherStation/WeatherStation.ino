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
*/
//--------------------------------------------------------------------
#include <Wire.h>
#include <U8g2lib.h>
#include <DHT.h>
#include <Seeed_BMP280.h>
//--------------------------------------------------------------------
#include "WeatherStruct.h"
#include "SensorCollection.h"
#include "DisplayToScreen.h"
//--------------------------------------------------------------------
#define DHTPIN 4 //Digital Pin DHT Sensor is connected to
#define DHTTYPE DHT11 //Type of DHT sensor being used
#define DHTCLOCK 3000
#define CLOCK 2000
//--------------------------------------------------------------------
U8G2_SSD1306_128X64_ALT0_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Type of Oled Screen, if you are using a different screen, reference U8g2 library for your screen and replace this variable
DHT dht(DHTPIN, DHTTYPE);
BMP280 bmp280;
WeatherRecord currentWeather;
unsigned long lastDHT = 0;
unsigned long lastUpdate = 0;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Wire1.begin();
  delay(50);
  dht.begin();
  if(!bmp280.init(0x77))
  {
    Serial.println("Pressure Sensor Error");
  }
  display.begin();

}

void loop() 
{
  unsigned long now = millis();

  //Clocktiming to ensure that DHT read timing isnt interrupted by other function calls
  if(now - lastDHT >= DHTCLOCK)
  {
    lastDHT = now;
    collectDHT(dht, currentWeather);
  }
  
  if(now - lastUpdate >= CLOCK)
  {
    lastUpdate = now;
    collectBMP(bmp280, currentWeather);
    displayToScreen(display, currentWeather);
  }
  
}
