//WeatherRecord.h - Header file containing a data structure that holds sensor results gathered by Arduino sensors
//--------------------------------------------------------------------
#ifndef WeatherRecord_H
#define WeatherRecord_H
//--------------------------------------------------------------------
#include "Classes/Date.h"
#include "Classes/Time.h"
//--------------------------------------------------------------------

		/**
		* @author Jordan Locke
		* @version 01
		* @typedef WeatherStruct
		* @struct WeatherStruct
		* @brief Stores weather data collected by Arduino sensors as well as date and time.
		 */

typedef struct WeatherRecord
{
	float ambAirTemp;
	float humidity;
	float pressureHpa;
	Date weatherDate;
	Time weatherTime;

	WeatherRecord(): weatherDate(0, 0, 0), weatherTime(0, 0), ambAirTemp(0), humidity(0), pressureHpa(0){}
} WeatherRecord;

//--------------------------------------------------------------------
#endif
