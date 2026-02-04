//DisplayToScreen.h - Header file for displaying sensor data to screen.
//--------------------------------------------------------------------
#ifndef DisplayToScreen_H
#define DisplayToScreen_H
//--------------------------------------------------------------------
//#include <string>
#include <U8x8lib.h>
#include "WeatherStruct.h"
//--------------------------------------------------------------------
#define Oled_Screen U8X8_SSD1306_128X64_NONAME_HW_I2C
//--------------------------------------------------------------------

//Initialises display, sets font, and orientation
void startDisplay(Oled_Screen& display);

//Update respective measurement from WeatherRecord if values change
void updateTemp(Oled_Screen& display, const int& newTemp);
void updateHumid(Oled_Screen& display, const int& newHumid);
void updatePress(Oled_Screen& display, const float& newPress);

//Displaying to console for testing purposes
void displayToConsole(WeatherRecord& currentWeather);

//--------------------------------------------------------------------
#endif //DisplayToScreen