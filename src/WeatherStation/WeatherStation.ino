/*
Author: Jordan Locke
Version: 1.0

The main function/sketch for the portable weather station project. 
This project is intended as an extension of a university assignment and a personal challenge to hone programming skills and learn electronics.
The purpose of this sketch is to initialise all pins and sensors connected to the Arduino before calling separate-
C++ modules to collect, store, and display weather data.
*/

#include "DHT.h"
#include "Seeed_BMP280.h"
#include <Wire.h>
#include <U8g2lib.h>
#include "WeatherStruct.h"
#include "SensorCollection.h"

#define DHTPIN 3 //Digital Pin DHT Sensor is connected to
#define DHTTYPE DHT11 //Type of DHT sensor being used

U8G2_SSD1306_128X64_ALT0_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Type of Oled Screen

DHT dht(DHTPIN, DHTTYPE);
BMP280 bmp280;
WeatherRecord currentWeather;

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
  // put your main code here, to run repeatedly:
  
collectDHT(dht, currentWeather);
collectBMP(bmp280, currentWeather);

/*
  Serial.print(F("Temp: "));
  Serial.print(temp);
  Serial.println("°C");
  Serial.print(F("Humid: "));
  Serial.print(humid);
  Serial.println("%");

  
  Serial.print(F("Pressure: "));
  Serial.print(hPressure);
  Serial.println("hPa");
*/

  //Display to Oled
  display.setFlipMode(1);
  display.clearBuffer(); //Clears internal memory
  display.setFont(u8g2_font_chroma48medium8_8r);

  display.setCursor(0, 10);
  display.print("Temp: ");
  display.print(currentWeather.ambAirTemp);
  display.print("C");

  display.setCursor(0, 20);
  display.print("Humid: ");
  display.print(currentWeather.humidity);
  display.print("%");

  display.setCursor(0, 30);
  display.print("Pres: ");
  display.print(currentWeather.pressureHpa);
  display.print("hPa");

  display.sendBuffer();


  Serial.println("\n");
  delay(2000);
}
