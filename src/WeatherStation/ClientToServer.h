//ConnectToServer.h - Definition file for functions related to connecting to a server and sending data over HTTP POST
/*
Much of this code has been extraced from the WiFiWebClient tutorial provided by Arduino.
I have slightly modified and modularised the code and provided my own comments to show my understanding of the WiFiS3 library.
To find this exact tutorial and more, please follow the link below:
https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/#wi-fi-web-client
*/
//--------------------------------------------------------------------
#ifndef ClientToServer_H
#define ClientToServer_H
//--------------------------------------------------------------------
#include "WiFiS3.h"
#include "server_secrets.h"
#include "weatherStruct.h"
//--------------------------------------------------------------------

//Connects to the server using IP and port provided in server_secret.h. This file is ignored by github for security reasons. Please create your own if you are using this repo.
//Currently uses IP rather than DNS for LAN testing
bool connectToServer(WiFiClient& client);

//Takes the current logged weather and appends it to POST body to be sent to server
void postData(WiFiClient& client, WeatherRecord& currentWeather);

//Reads response from server. Mainly for debugging purposes
void readResponse(WiFiClient& client);

//Disconnects Arduino from server
bool disconnectFromServer(WiFiClient& client);

//--------------------------------------------------------------------
#endif //ClientToServer_H