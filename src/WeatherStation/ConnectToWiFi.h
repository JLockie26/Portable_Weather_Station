//ConnectToWifi.h - Definition file for functions related to connecting to local network
/*
Much of this code has been extraced from the WiFiWebClient tutorial provided by Arduino.
I have slightly modified and modularised the code and provided my own comments to show my understanding of the WiFiS3 library.
To find this exact tutorial and more, please follow the link below:
https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/#wi-fi-web-client
*/
//--------------------------------------------------------------------
#ifndef ConnectToWifi_H
#define ConnectToWifi_H
//--------------------------------------------------------------------
#include "WiFiS3.h"
#include "wifi_secrets.h"
//--------------------------------------------------------------------

//Determines if device has a wifi module installed (e.g ESP32-S3) and checks for latest firmware
bool checkWifiModule();

//Connects to network using details provided in wifi_secrets.h. This file is ignored by github for security reasons. Please create your own if you are using this repo
int connectToNetwork();

//--------------------------------------------------------------------
#endif //ConnectToWiFi_H