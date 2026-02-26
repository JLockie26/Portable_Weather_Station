//ClientToServe.cpp - Implementation file for client-server related functions
//--------------------------------------------------------------------
#include "ClientToServer.h"
//--------------------------------------------------------------------
bool connectToServer(WiFiClient& client)
{
  IPAddress server(SERVER_IP);
  Serial.println("Connecting to server...");
  if(client.connect(server, SERVER_PORT))
  {
    Serial.println("Connected to server");
    return true;
  }
  else
  {
    Serial.println("Connection Failed");
    return false;
  }
}
//--------------------------------------------------------------------
void postData(WiFiClient& client, WeatherRecord &currentWeather)
{
  IPAddress server(SERVER_IP);
  String postBody = "{";
  postBody += "\"temp\":";
  postBody += currentWeather.ambAirTemp;
  postBody += ",\"humid\":";
  postBody += currentWeather.humidity;
  postBody += ",\"press\":";
  postBody += currentWeather.pressureHpa;
  postBody += "}";

  int contentLength = postBody.length();

  // Make a HTTP POST request
  client.print("POST /api/weather/ HTTP/1.1\r\n");
  client.print("Host: ");
  client.print(server);
  client.print(":");
  client.print(SERVER_PORT);
  client.print("\r\n");
  client.print("Content-Type: application/json\r\n");
  client.print("Content-Length: "); // required even if body is empty
  client.print(contentLength);
  client.print("\r\n");
  client.print("\r\n"); // blank line separating headers from body

  //Send body
  client.print(postBody);

}
//--------------------------------------------------------------------
void readResponse(WiFiClient& client)
{
  uint32_t received_data_num = 0;
  while(client.available())
  {
    //Get response data recieved from server
    char c = client.read();
    Serial.print(c);

    //Wrap data to 80 columns
    received_data_num++;
    if(received_data_num % 80 == 0)
      Serial.println();
  }
}
//--------------------------------------------------------------------
bool disconnectFromServer(WiFiClient& client)
{
  Serial.println("Disconnecting from server");
  client.stop();

  return false;
}
//--------------------------------------------------------------------