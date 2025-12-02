# Portable Arduino Weather Station

This Arduino-based weather station project is a personal extension outside of a university assignment.
The initial assignment had students take weather data produced by Murdoch University's weather station and process it in various ways. This project will initially focus on collecting the data for processing, before moving onto monitoring and comparing weather statistics via web-based application.

Goals of this repository:
- Show progression of features over time.
- Demonstrate and revise knowledge of OOP, Data Structures & Abstraction, and Web Development.
- Learn and understand more about computer hardware.


## Features (current iteration)
- Reads temperature(Celsius), humidity, and air pressure(Hectopascals).
- Logs readings to serial (SD card logging in progress)
- Outputs current readings to OLED display

First iteration focus was to understand how to use and program an Arduino, hence the simple coding. Next iteration will focus on introducing SD card storage and modular code.


## Repository Structure
```
WeatherStation_Project/
├───docs
├───src
│   └───WeatherStation
│       └───Classes
└───tests
    ├───DHTtester_NoKit
    ├───BaroTest_NoKit
    └───ReadWrite
```


## Getting Started
1. Install Arduino IDE. Used to write .ino files and upload to Arduino. Visual Studio and VSCode have been used to write code outside .ino file. (There is a VSCode extension to write and upload to Arduino, but for beginners sake, Arduino IDE is best option)
2. Install required libraries via Arduino IDE (Recommended) or download:
    - [Grove_Temperature_And_Humidity_Sensor](https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor)
    - [Grove_-_Barometer_Sensor_BMP280](https://github.com/Seeed-Studio/Grove_BMP280)
    - Wire Library - This is included with Arduino IDE.
    - [u8g2 Library - For OLED Display](https://github.com/olikraus/u8g2)
3. Download or clone repo.
4. Connect components (component list and wirechart WIP)
5. Open src/WeatherStation.ino and upload to arduino!



## Hardware Used
- Arduino Uno R4 WiFi
- Arduino Sensor Kit or the following sensors:
    - [Grove Base Shield](https://wiki.seeedstudio.com/Base_Shield_V2/)
    - [Grove DHT11 Sensor](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)
    - [Grove BMP280 Sensor](https://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP280/)
    - [Grove OLED Display 0.96 inch](https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/)

Note: Alternatively, a Arduino Uno R3 along with the Arduino Sensor Kit library could be used to set up the current iteration of this project (which would be much simpler). But because of future plans to implement transmission of data over WiFi, this repo is designed to be used with an Uno R4 Wifi, using seperate libraries to avoid clock timing incompatabilities between the sensor kit library and the R4 architecture. 


## Future Additions
- SD card logging - To write to a CSV file that will be processed on uni assignment program (program will not be included in repo as to avoid academic misconduct)
- Wireless transmission of weather data to web server
- Storing, processing, and comparing weather data on web server
- Sensor upgrades & additional sensors (air quality, rain detection, soil humidity, etc)