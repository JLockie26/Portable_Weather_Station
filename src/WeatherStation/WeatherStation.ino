/*
Author: Jordan Locke
Current Version: 0.6
Please read device-CHANGELOG.md for previous implementations

@todo Do something with sensor failures, this ties into creating error codes that display on screen
@todo Revamp current screen functionality, replace with error codes / status
@todo Consider timing re-connects as to not stall device if network is down for a while
@todo Main file has a lot of globals, consider creating a controller module to neaten up main
@todo Implement function to send logs in batch once device reconnects to wifi and server (do this once bugs are fixed and screen displays error codes)
*/
//--------------------------------------------------------------------
#include <Wire.h>
#include <U8x8lib.h>
#include <DHT.h>
#include <Seeed_BMP280.h>
#include <SD.h>
#include "WiFiS3.h"
//--------------------------------------------------------------------
#include "WeatherStruct.h"
#include "SensorCollection.h"
#include "DisplayToScreen.h"
#include "SensorLogging.h"
#include "RTC.h"
#include "ConnectToWiFi.h"
#include "ClientToServer.h"
//--------------------------------------------------------------------
#define SERIALPORT 9600 //Port number Arduino communicates to PC via serial
#define DHTTYPE DHT11 //Type of DHT sensor being used
#define DHTPIN 2 //Digital Pin DHT Sensor is connected to
#define BMDADDR 0x77 //I2C address of BMP sensor
#define _PIN_SDA SDA
#define _PIN_SCL SCL
#define Oled_Screen U8X8_SSD1306_128X64_NONAME_HW_I2C
//--------------------------------------------------------------------
Oled_Screen display(_PIN_SCL, _PIN_SDA, U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);
BMP280 bmp280;
WeatherRecord currentWeather;
unsigned long lastLog = 0;
const unsigned long LOGCLOCK = 300000; //5 min interval test
const unsigned long STATE_DELAY = 20;
static unsigned long stateTimeStamp = 0;
const int chipSelect = 4;
unsigned long now;
float lastTemp = 0.0f;
float lastHumid = 0.0f;
float lastPress = 0.0f;
RTCTime currentTime;
int wifiStatus = WL_IDLE_STATUS;
int attemptLimit = 3;
int connectionAttempts = 0;
bool usingWifi = false;
WiFiClient client;
bool clientConnected = false;

enum SampleState
{
  IDLE,
  DHT_COLLECTED,
  BMP_COLLECTED,
  BUS_IDLE,
  DISPLAY_COMPLETED,
  TIME_LOGGED
};
SampleState sampleState = SampleState::IDLE;
//--------------------------------------------------------------------
void setup() 
{
  //Initialise all components
  Serial.begin(SERIALPORT);
  Wire.begin();
  delay(50); //Gives time for I2C to initialise
  dht.begin();
  if(!bmp280.init(BMDADDR))
  {
    Serial.println("Pressure Sensor Error");
  }
  initialiseSD(chipSelect);
  startDisplay(display);
  RTC.begin();

  //Start hard-coded time(REMOVE THIS, REPLACE WITH SNTP/TIME REQUEST FROM SERVER)
  RTCTime startTime(28, Month::JANUARY, 2025, 12, 0, 0, DayOfWeek::SATURDAY, SaveLight::SAVING_TIME_INACTIVE);
  RTC.setTime(startTime);

  //Attempt WiFi connection
  usingWifi = checkWifiModule();
  if(usingWifi)
  {
    while(connectionAttempts < attemptLimit && wifiStatus != WL_CONNECTED)
    {
      wifiStatus = connectToNetwork();
      connectionAttempts++;
      if(wifiStatus != WL_CONNECTED)
      {
        Serial.print("Connection failed, attempt: ");
        Serial.println(connectionAttempts);
      }
    }
    if(connectionAttempts >= attemptLimit)
    {
      Serial.println("Too many failed attempts, program will retry later");
    }
  }
  else 
  {
    Serial.println("Device will not use wifi");
  }

  //Begin initial log
  lastLog = millis() - LOGCLOCK;
  sampleState = SampleState::IDLE;
}

void loop() 
{
  RTC.getTime(currentTime);
  now = millis();
  

  //Non-blocking delay between DHT capture and other sensors
  if(sampleState == SampleState::IDLE && now - lastLog >= LOGCLOCK)
  {
    Serial.println("Collecting DHT");
    collectDHT(dht, currentWeather);
    stateTimeStamp = now;
    sampleState = SampleState::DHT_COLLECTED;
  }


  else if(sampleState == SampleState::DHT_COLLECTED && now - stateTimeStamp >= STATE_DELAY)
  {
    Serial.println("Collecting BMP");
    collectBMP(bmp280, currentWeather);
    stateTimeStamp = now;
    sampleState = SampleState::BMP_COLLECTED;
  }

  else if(sampleState == SampleState::BMP_COLLECTED && now - stateTimeStamp >= STATE_DELAY)
  {
    sampleState = SampleState::BUS_IDLE;
    stateTimeStamp = now;
  }

  else if(sampleState == SampleState::BUS_IDLE && now - stateTimeStamp >= STATE_DELAY)
  {
    
    //Only update the measurements that change (should avoid sending too much data over SDA hopefully)
    if(fabs(currentWeather.ambAirTemp - lastTemp) > 0.1f)
    {
      Serial.println("Updating Temp");
      updateTemp(display, currentWeather.ambAirTemp);
      lastTemp = currentWeather.ambAirTemp;
    }
    
    if(fabs(currentWeather.humidity - lastHumid) > 0.1f)
    {
      Serial.println("Updating Humid");
      updateHumid(display, currentWeather.humidity);
      lastHumid = currentWeather.humidity;
    }

    if(fabs(currentWeather.pressureHpa - lastPress) > 0.1f)
    {
      Serial.println("Updating Press");
      updatePress(display, currentWeather.pressureHpa);
      lastPress = currentWeather.pressureHpa;
    }
      
    stateTimeStamp = now;
    sampleState = SampleState::DISPLAY_COMPLETED;
  }

  else if(sampleState == SampleState::DISPLAY_COMPLETED && now - stateTimeStamp >= STATE_DELAY)
  {
    Serial.println("Logging Time");
    collectDateTime(currentWeather, currentTime);
    stateTimeStamp = now;
    sampleState = SampleState::TIME_LOGGED;
  }

  else if(sampleState == SampleState::TIME_LOGGED && now - stateTimeStamp >= STATE_DELAY)
  {
    //Log to SD if not using WiFi or cannot connect to WiFi
    if(wifiStatus != WL_CONNECTED)
    {
      Serial.println("Logging to SD Card");
      logWeatherData(currentWeather);

      //Attempt reconnect
      wifiStatus = connectToNetwork();
      if(wifiStatus == WL_CONNECTED)
      {
        Serial.println("WiFi Connection Success!");
        Serial.println("Sending SD Logs..."); //TESTING SUCCESS MESSAGE
      }
      else
      {
        Serial.println("Reconnection to WiFi failed");
      }

      endSampleCycle();
      return;
    }

    //Log to SD card in event of bad request or server connection failure
    clientConnected = connectToServer(client);
    if(!clientConnected)
    {
      Serial.println("Cannot Connect To Server - Logging to SD Card");
      logWeatherData(currentWeather);
      endSampleCycle();
      return;
    }

    postData(client, currentWeather);
    readResponse(client);
    //Put response check here
    clientConnected = disconnectFromServer(client);

    endSampleCycle();
  }
  //End of Loop
}

void endSampleCycle() //This should eventually be moved into a sample state controller module. Main becoming wayy too cluttered
{
    Serial.println("Sample Cycle Completed");
    lastLog = now;
    stateTimeStamp = now;
    sampleState = SampleState::IDLE;
}
