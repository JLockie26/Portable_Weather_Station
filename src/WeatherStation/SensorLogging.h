//SensorLogging.h - Header file for sensor logging related functions
#ifndef SensorLogging_H
#define SensorLogging_H
//--------------------------------------------------------------------
#include <SD.h>
#include "WeatherStruct.h"
//--------------------------------------------------------------------

/*
Initialises SD card using chipSelect variable.
If card is not initialised properly, debugging instructions display in Serial Monitor.
*/
void initialiseSD(const int chipSelect);
void logWeatherData(WeatherRecord& currentWeather);
void newFile(String& fileName);
void testLog(String& fileName);

//--------------------------------------------------------------------
#endif //SensorLogging_H
