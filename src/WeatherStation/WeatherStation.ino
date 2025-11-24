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
//#include "WeatherStruct.h" - Set up to store weather data on SD card

#define DHTPIN 3 //Digital Pin DHT Sensor is connected to
#define DHTTYPE DHT11 //Type of DHT sensor being used

U8G2_SSD1306_128X64_ALT0_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Type of Oled Screen

DHT dht(DHTPIN, DHTTYPE);
BMP280 bmp280;

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
  

  //Record Temp&Humid
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  //Record Baro Pressure (Hectopascals)
  int hPressure = bmp280.getPressure() / 100;

  // Check if any reads failed and exit early (to try again).
  if(isnan(humid) || isnan(temp)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if(isnan(hPressure))
  {
    Serial.println(F("Failed to read from BMP sensor!"));
    return;
  }

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

  //Display it to Oled
  display.setFlipMode(1);
  display.clearBuffer(); //Clears internal memory
  display.setFont(u8g2_font_chroma48medium8_8r);

  display.setCursor(0, 10);
  display.print("Temp: ");
  display.print(temp);
  display.print("C");

  display.setCursor(0, 20);
  display.print("Humid: ");
  display.print(humid);
  display.print("%");

  display.setCursor(0, 30);
  display.print("Pres: ");
  display.print(hPressure);
  display.print("hPa");

  display.sendBuffer();


  Serial.println("\n");
  delay(2000);
}
