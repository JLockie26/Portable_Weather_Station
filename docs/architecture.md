# Architecture Overview

Current Goal: The current purpose of this portable arduino weather station is to act as a stand alone machine that collects and stores sensor data which is then displayed on a screen. Future iterations will see the machine interact with a web-server to provide more than standalone capabilities.

## Code & Flow Overview

Coding for the weather station in current iteration is simple and introduces user and creator to working with hardware. Next iteration will include modularisation of components and data structures.
### Current Flow
1. Define sensors and connected pins on Arduino
2. Initialise sensors and display
3. Begin main program loop
4. Read temp, humidity, and pressure values. Values are valid (not NAN)
5. Format display and print values
6. After a given interval, log current weather values to CSV file on SD card
7. End loop

## WeatherRecord Struct
A data structure that will aggregate all sensor data to be stored, displayed, and later transmitted. Structure will be active and in use next iteration.
- ambAirTemp: A float to store temperature in degrees celcius
- humidity: A float to store humidity %
- pressureHpa: A float to store air pressure in hectopascals
- date: A DateTime struct to store the date and time the weather was recorded.

## DateTime Struct
A data structure that will store the values representing date and time gathered by the RTC module.
- year: An integer to store a year value.
- month: An integer to store a month value (1 - 12).
- day: An integer to store a day value (1 - 31).
- hour: An integer to store an hour value (0 - 23)
- minute: An integer to store a minute value (0 - 59).