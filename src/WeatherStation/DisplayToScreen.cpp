//DisplayToScreen.cpp - Implementation file for displaying to OLED screen
//--------------------------------------------------------------------
#include "DisplayToScreen.h"
//--------------------------------------------------------------------
void startDisplay(Oled_Screen& display)
{
  //Initialise display, position, and font
  display.begin();
  display.setFlipMode(1);
  display.setFont(u8x8_font_chroma48medium8_r);

  //Set headers
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.setCursor(0, 10);
  display.print("Humid: ");
  display.setCursor(0, 20);
  display.print("Pres: ");
}
//--------------------------------------------------------------------
void updateTemp(Oled_Screen& display, const int& newTemp)
{
  display.setCursor(6, 0);
  display.print(newTemp);
  display.print("C");
}
//--------------------------------------------------------------------
void updateHumid(Oled_Screen& display, const int& newHumid)
{
  display.setCursor(7, 10);
  display.print(newHumid);
  display.print("%");
}
//--------------------------------------------------------------------
void updatePress(Oled_Screen& display, const float& newPress)
{
  display.setCursor(6, 20);
  display.print(newPress, 1);
  display.print("hPa");
}
//--------------------------------------------------------------------
void displayToConsole(const WeatherRecord& currentWeather)
{
  //Temp
  Serial.print("Temp: ");
  Serial.print(currentWeather.ambAirTemp);
  Serial.println("C");

  //Humid
  Serial.print("Humid: ");
  Serial.print(currentWeather.humidity);
  Serial.println("%");

  //Pressure
  Serial.print("Press: ");
  Serial.print(currentWeather.pressureHpa);
  Serial.println("hPa");
}
//--------------------------------------------------------------------