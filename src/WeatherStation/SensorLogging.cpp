//SensorLogging.cpp - Implementation file for sensor logging related functions.
//--------------------------------------------------------------------
#include "SensorLogging.h"
#include "DisplayToScreen.h"
//--------------------------------------------------------------------

void initialiseSD(const int chipSelect)
{
  Serial.print("Initialising SD Card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");


}

void logWeatherData(WeatherRecord& currentWeather)
{
  File dataFile;
  String fileName = "ArduinoTest.csv";
	
  if(!SD.exists(fileName))
    newFile(fileName);

  dataFile = SD.open(fileName, FILE_WRITE);
  if(dataFile)
  {
    //Print date under WAST column
    dataFile.print(currentWeather.date.day);
    dataFile.print("/");
    dataFile.print(currentWeather.date.month);
    dataFile.print("/");
    dataFile.print(currentWeather.date.year);
    dataFile.print(" ");
    dataFile.print(currentWeather.date.hour);
    dataFile.print(":");
    dataFile.print(currentWeather.date.minute);
    dataFile.print(",");
    
    //Print weather data in order of columns
    dataFile.print(currentWeather.ambAirTemp);
    dataFile.print(",");
    dataFile.print(currentWeather.humidity);
    dataFile.print(",");
    dataFile.println(currentWeather.pressureHpa);
    dataFile.close();
  }
  else
    Serial.println("Error Opening File");

}

void newFile(String& fileName)
{
  File dataFile = SD.open(fileName, FILE_WRITE);
  if(dataFile)
  {
    dataFile.println("WAST, T, RH, QFE");
    dataFile.close();
  }
  else
    Serial.println("Error Opening File");
  
}

/*
void testLog(String& fileName)
{
  File dataFile = SD.open(fileName, FILE_READ);
  if(dataFile)
  {

    // read from the file until there's nothing else in it:
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }

    dataFile.close();
  }
  else
    Serial.println("Error Opening File");

}
*/