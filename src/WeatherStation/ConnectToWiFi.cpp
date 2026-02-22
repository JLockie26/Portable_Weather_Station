//ConnectToWiFi.cpp - Implementation file for local network functions
//--------------------------------------------------------------------
#include "ConnectToWiFi.h"
//--------------------------------------------------------------------

bool checkWifiModule()
{
  String fv = WiFi.firmwareVersion();

  //Check for chip, return false if no chip detected. This will still allow the program to run, but without wifi functionality
  if(WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed.");
    Serial.println("Pleae use a board with an integrated wifi module or connect one to your current board.");
    Serial.println("If you have a module installed and are seeing this message, your module may be damaged, incompatible with the WiFiS3 library, or not installed properly.");

    return false;
  }

  if(fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade firmware");
  }

  return true;
}

int connectToNetwork()
{
  char ssid[] = SECRET_SSID;
  char pass[] = SECRET_PASS;

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  int status = WiFi.begin(ssid, pass); //Assuming user will connect to a WPA/WPA2 network

  //Wait for connection - 5sec
  delay(5000);

  return status;
}

//--------------------------------------------------------------------