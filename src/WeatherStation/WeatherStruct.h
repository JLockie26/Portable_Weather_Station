//WeatherRecord.h - Header file containing a data structure that holds sensor results gathered by Arduino sensors
//--------------------------------------------------------------------
#ifndef WeatherRecord_H
#define WeatherRecord_H
//--------------------------------------------------------------------

		/**
		* @author Jordan Locke
		* @version 02
		* @typedef WeatherRecord
		* @struct WeatherRecord
		* @brief Stores weather data collected by Arduino sensors as well as date and time.
		*				 Date and Time classes are now structs. RTC takes care of controlling date & time validation
		*
		*	@author Jordan Locke
		*	@version 01
		*	@typedef DateTime
		*	@struct DateTime
		*	@brief Stores date time data collected by the RTC module
		 */

typedef struct DateTime
{
	int year, month, day, hour, minute;

}DateTime;

typedef struct WeatherRecord
{
	int ambAirTemp; //Degrees Celcius
	int humidity; //Percentage
	float pressureHpa; //HectoPascals (hPa)
	DateTime date;
} WeatherRecord;

//--------------------------------------------------------------------
#endif
