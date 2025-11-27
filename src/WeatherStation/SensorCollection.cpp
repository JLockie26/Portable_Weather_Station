//SensorCollection.cpp - Implementation file for collecting & reading sensor data
//--------------------------------------------------------------------
#include "SensorCollection.h"
//--------------------------------------------------------------------

//Collect date and time from built-in RTC. Date and Time will be hardcoded until system is connecting to web server
void collectDateTime(WeatherRecord& currentWeather)
{
	//Do nothing for now
}

//Collects temp & humidity values
void  collectDHT(DHT& dht, WeatherRecord& currentWeather)
{
  //Read and Check
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  if(isnan(humid) || isnan(temp)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //Record Temp&Humid
	currentWeather.ambAirTemp = temp;
	currentWeather.humidity = humid;
}

//Collects pressure values
void collectBMP(BMP280& bmp280, WeatherRecord& currentWeather)
{
  int hPressure = bmp280.getPressure() / 100;
  if(isnan(hPressure))
  {
    Serial.println(F("Failed to read from BMP sensor!"));
    return;
  }

  //Record Baro Pressure (Hectopascals)
  currentWeather.pressureHpa = hPressure;
}

//--------------------------------------------------------------------