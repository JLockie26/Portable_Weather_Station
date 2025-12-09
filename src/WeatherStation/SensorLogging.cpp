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

void logWeatherData()
{
  File dataFile;
  String fileName = "test.csv";
	
  

}