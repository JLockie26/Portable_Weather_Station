//SensorCollection.cpp - Implementation file for collecting & reading sensor data
//--------------------------------------------------------------------
#include "SensorCollection.h"
//--------------------------------------------------------------------

//Collect date and time from built-in RTC. Date and Time will be hardcoded until system is connecting to web server
void collectDateTime(WeatherRecord& currentWeather, RTCTime& currentTime)
{
  //Set current weather's DateTime struct to current date and time
  currentWeather.date.day = currentTime.getDayOfMonth();
  currentWeather.date.month = Month2int(currentTime.getMonth());
  currentWeather.date.year = currentTime.getYear();

  currentWeather.date.hour = currentTime.getHour();
  currentWeather.date.minute = currentTime.getMinutes();
}
//--------------------------------------------------------------------
//Collects temp & humidity values
void  collectDHT(DHT& dht, WeatherRecord& currentWeather)
{
  //Read and Check
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  if(isnan(temp)) 
  {
    Serial.println(F("Failed to read from temp!"));
    return;
  }
  else if(isnan(humid))
  {
    Serial.println("Failed to read humid!");
    return;
  }
  //Record
	currentWeather.ambAirTemp = temp;
  currentWeather.humidity = humid;
}
//--------------------------------------------------------------------
//Collects pressure values
void collectBMP(BMP280& bmp280, WeatherRecord& currentWeather)
{
  float hPressure = bmp280.getPressure() / 100.0f;
  if(isnan(hPressure) || hPressure <= 0.0f)
  {
    Serial.println(F("Failed to read from BMP sensor!"));
    return;
  }
  //Record Baro Pressure (Hectopascals)
  currentWeather.pressureHpa = hPressure;
}
//--------------------------------------------------------------------