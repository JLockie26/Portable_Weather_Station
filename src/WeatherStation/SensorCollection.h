//SensorCollection.h - A header file that defines functions for sensor data collection
//--------------------------------------------------------------------
#ifndef SensorCollection_H
#define SensorCollection_H
//--------------------------------------------------------------------
#include "DHT.h"
#include "Seeed_BMP280.h"
#include "WeatherStruct.h"
//--------------------------------------------------------------------

void collectDateTime(WeatherRecord& currentWeather);

void collectDHT(DHT& dht, WeatherRecord& currentWeather);

void collectBMP(BMP280& bmp280, WeatherRecord& currentWeather);

#endif
