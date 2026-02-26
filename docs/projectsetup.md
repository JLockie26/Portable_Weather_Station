# Project Setup

This document will explain how to set up all aspects of the project. **It is assumed you are working with the [Arduino Sensor Kit](https://core-electronics.com.au/arduino-sensor-kit-base.html), if you choose to buy individual sensors, results may differ and program may not work as intended**. The code in this project has been designed in a way that it is not reliant on the Grove shield included with the kit, but due to time and budget constraints, code has not been tested on different hardware configurations. This may change in future iterations to keep the project hardware modular.

If there are any issues with code after installing libraries and following instructions, contact me via my email on my GitHub profile, or log an issue on the page. I will do my best to respond as soon as I can and fix the issue. Please note however this is a side project and as a student I may not be able to fix things immediately.


## Setting Up Arduino
### Assumptions
- You are using an Arduino Uno R4 WiFi.
- You are using the sensors listed in the README file. Grove shield is optional but makes installing sensors very convienient.
- You are using latest version of Arduino IDE to upload, view, and modify Arduino-related code.
- You are using VSCode to view and edit server-related code.
- You are using Node version 20.11.0 or later.
- You will be connecting to a personal WPA/WPA2 local network. Please do not connect this device to public networks.

### Arduino Hardware
- Place Grove Shield over the top of Arduino, ensuring it is securely connected
- Connect DHT sensor into D2 port on shield
- Connect BMP sensor & OLED screen into I2C ports (any should be fine)
- Follow [wiring document](./wiring.md) to connect SD card module
- Set shield to 3.3v (this is important as sensors or screen may fail at 5v. If not using shield, wire components from 3.3v pin)
- Setup is now complete. Feel free to connect Arduino to machine.

### Libraries Required
Search for these libraries in Arduino Library Manager.
- Grove Temperature and Humidity Sensor by Seeed Studio
- Grove - Barometer Sensor BMP280 by Seeed Studio
- U8g2 by Oliver
- SD by Arduino, Sparkfun
- Wire, WiFiS3, and RTC should be pre-installed if you have connected an Arduino Uno R4 WiFi to the IDE

### Arduino Software
- Clone or download repo to local drive
- Follow path: Portable_Weather_Station -> src -> WeatherStation -> WeatherStation.ino
- Open WeatherStation.ino in Arduino IDE
- Go to ... on top right corner of Arduino IDE or press "ctrl+shift+N".
- Create a file named "wifi_secrets.h".
- Define the following variables:
    ```C++
    #define SECRET_SSID "Enter your wifi name here"
    #define SECRET_PASS "Enter your password here"
    ```
- Follow same steps to create a file named "server_secrets.h"
- Define the following variables, where X represents your own numbers:
- For SERVER_IP: This will be the IP that the server is running on (most likely your local machine. Find your IP before defining)
    ```C++
    #define SERVER_IP X,X,X,X //Each X represents an octet of an IP address (e.g: 192.168.1.1)
    #define SERVER_PORT X //This will be the port your server listens on. Common HTTP ports are 80 and 8080
    ```
- Verify code to ensure no errors (check symbol in top left corner)
- Upload code using the arrow symbol next to check symbol.
- Your arduino should now be operating as a small portable weather station!
- Note if you set up arduino before activating your server, you will not transmit data to the server. Data will still log in SD card if one is attached, although date and time will be incorrect. This will be changed in future updates

## Setting Up NodeJS Server
- Assuming you have cloned or downloaded the repo.
- Follow path: Portable_Weather_Station -> src -> NodeServer -> server.js
- Open server.js in VSCode
- Note that const port on line 12 is set to 8080. Change this to whichever port you defined in "server_secrets.h".
- Open up terminal and run command "node server.js"
- Server should now be listening on the port you specified.
- To view client page, to go "http://localhost:yourPortNumber/" (changing yourPortNumber to the number you specified)
- You should be able to see client page. If you have not yet sent any data from the Arduino, the numbers on the website will be "undefined". This is intentional and will change in future updates.

## Combining Server and Arduino
If you have both Arduino and server running, you should see the numbers update to live weather readings either instantly or about a minute. It is recommended you start the server first then start the Arduino for quickest results. The arduino will gather weather samples every 5 minutes, the client page will fetch results from the server every minute. If any errors occure on either server or Arduino, resetting the arduino and/or restarting the server is the best course of action.