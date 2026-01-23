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

//Takes reference for screen and current weather struct, displays struct data to screen
void displayToScreen(Oled_Screen& display, WeatherRecord& currentWeather);

//--------------------------------------------------------------------
#endif //DisplayToScreen