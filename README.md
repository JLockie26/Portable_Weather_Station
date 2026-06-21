# Portable Arduino Weather Station

This Arduino-based weather station project is a personal extension outside of a university assignment.
The initial assignment had students take weather data produced by Murdoch University's weather station and process it in various ways. This project will initially focus on collecting the data for processing, before moving onto monitoring and comparing weather statistics via web-based application.

Goals of this repository:
- Show progression of features over time.
- Demonstrate and revise knowledge of OOP, Data Structures & Abstraction, and Web Development.
- Learn and understand more about systems programming, web programming, client-server architecture, and electronics

## Project Status
**Current Iteration** v0.2 - Arduino to Node.js Integration

**Status:** Active Development

Development is now active and implementations of roadmap will begin! No release schedule is currently in place as I will be working around job schedule, but I plan to polish off a lot of this project before semester starts end of July.


## Features
- Reads temperature(Celsius), humidity, and air pressure(Hectopascals).
- Logs measurements to SD Card
- Display current measurements to OLED screen
- Sends data via HTTP POST to a Node.js server
- Stores readings in a JSON log file
- Serves a basic frontend for viewing recent readings

Learn how to set up the project [here](./docs/projectsetup.md)

## Architecture Overview

Arduino -> HTTP POST -> Node.js Server -> JSON Storage -> Frontend Fetch request to Client

## Current Limitations
- Race conditions exist. If timed right, server may not update live weather.
- No Database usage
- Limited to no API authentication or rate limiting
- Minimal client-side and server-side validation
- Past weather logs not displayed yet
- Local network functionality only

## Roadmap

### v0.3
- Improve client and server validation and security
- Improve and update client web-page functionality
- Add structured logging
- Refactor usage of SD card module and OLED module

### v0.4
- Implement database such as MongoDB or MySQL, replace JSON  storage
- Implement retention policies and security
- Implement historical visualisation of data, comparisons, and correlation

### v0.5 
- Consider handling more Arduino stations to create a dense data map of weather for a local area
- Consider adding more sensors, such as rain detection, air quality, soil humidity, etc
- Consider comparison of local data to other weather APIs in same location


## Repository Structure
```
Portable_Weather_Station
   ├───docs
   └───src
       ├───WeatherStation
       └───Node Server
           ├───data
           ├───public
           │   ├───css
           │   ├───js
           │   └───html
           ├───routes
           └───utils
```



## Technologies Used
### Arduino Device (C++)
- Arduino Uno R4 WiFi
- Arduino Sensor Kit or the following sensors:
    - [Grove Base Shield](https://wiki.seeedstudio.com/Base_Shield_V2/)
    - [Grove DHT11 Sensor](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)
    - [Grove BMP280 Sensor](https://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP280/)
    - [Grove OLED Display 0.96 inch](https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/)
    - [XC4386 SD Card Module](https://media.jaycar.com.au/product/resources/XC4386_manualMain_78737.pdf)

### Backend
- Node.js
- JSON file storage
- HTML, CSS, Javascript
