//DisplayToScreen.cpp - Implementation file for displaying to OLED screen
//--------------------------------------------------------------------
#include "DisplayToScreen.h"
//--------------------------------------------------------------------

void startDisplay(Oled_Screen& display)
{
  display.begin();
  display.setFlipMode(1);
  display.setFont(u8x8_font_chroma48medium8_r);
}

//--------------------------------------------------------------------
void displayToScreen(Oled_Screen& display, WeatherRecord& currentWeather)
{ 
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(currentWeather.ambAirTemp);
  display.print("C");

  display.setCursor(0, 10);
  display.print("Humid: ");
  display.print(currentWeather.humidity);
  display.print("%");

  display.setCursor(0, 20);
  display.print("Pres: ");
  display.print(currentWeather.pressureHpa);
  display.print("hPa");
}
//--------------------------------------------------------------------