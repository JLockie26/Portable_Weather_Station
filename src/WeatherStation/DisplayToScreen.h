//DisplayToScreen.h - Header file for displaying sensor data to screen.
//--------------------------------------------------------------------
#ifndef DisplayToScreen_H
#define DisplayToScreen_H
//--------------------------------------------------------------------
//#include <string>
#include <U8g2lib.h>
#include "WeatherStruct.h"
//--------------------------------------------------------------------

//Takes reference for screen and current weather struct, displays struct data to screen
void displayToScreen(U8G2_SSD1306_128X64_ALT0_F_HW_I2C& display, WeatherRecord& currentWeather);
void displayError(String& error);

//--------------------------------------------------------------------
#endif //DisplayToScreen