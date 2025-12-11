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
    - [SD by Arduino & Sparkfun](https://github.com/arduino-libraries/SD)
    - RTC library - Included once Arduino R4 WiFi board is detected by Arduino IDE
3. Download or clone repo.
4. Connect components (wirechart WIP)
5. Open src/WeatherStation.ino and upload to arduino!



## Hardware Used
- Arduino Uno R4 WiFi
- Arduino Sensor Kit or the following sensors:
    - [Grove Base Shield](https://wiki.seeedstudio.com/Base_Shield_V2/)
    - [Grove DHT11 Sensor](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)
    - [Grove BMP280 Sensor](https://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP280/)
    - [Grove OLED Display 0.96 inch](https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/)
    - [XC4386 SD Card Module](https://media.jaycar.com.au/product/resources/XC4386_manualMain_78737.pdf)


## Future Additions
- ~~SD card logging - To write to a CSV file that will be processed on uni assignment program~~(program will not be included in repo as to avoid academic misconduct)
- Wireless transmission of weather data to web server
- Storing, processing, and comparing weather data on web server
- Sensor upgrades & additional sensors (air quality, rain detection, soil humidity, etc)