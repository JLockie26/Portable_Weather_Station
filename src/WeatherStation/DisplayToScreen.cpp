//DisplayToScreen.cpp - Implementation file for displaying to OLED screen
//--------------------------------------------------------------------
#include "DisplayToScreen.h"
//--------------------------------------------------------------------

void displayToScreen(U8G2_SSD1306_128X64_ALT0_F_HW_I2C& display, WeatherRecord& currentWeather)
{
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
}

//--------------------------------------------------------------------