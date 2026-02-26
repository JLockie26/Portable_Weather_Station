# Architecture Overview

Current Goal: The current purpose of this portable arduino weather station is to act as a stand alone machine that collects and stores sensor data which is then displayed on a screen. If wifi is connected, the most recent collected is transmitted via HTTP POST to a web server, where it is diplayed to a client-web page.

## Code & Flow Overview

Coding for the weather station in current iteration is simple and introduces user and creator to working with hardware. Next iteration will include modularisation of components and data structures.
### Current Arduino Flow
1. Define sensors and connected pins on Arduino
2. Initialise sensors, SD card, display
3. Check wifi connection, attempt 3 times before aborting wifi connectivity
4. Begin main program loop
5. Check time since last log and compare to interval time
6. If last log is past interval time:
    - Collect sensor data
    - Display values to screen
    - Log to SD card
    - If WiFi is connected:
        - Connect to server
        - Request POST data transmission to server
        - Read server response
        - Disconnect from server
8. End loop

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

### Current Sever Flow
1. Create an asynchronous server
2. Listen for following requests:
    - Client Page
        - Serve index.html and other static files requested from client
    - Client live weather upates
        - Serve latest entry from weatherLog.JSON
    - POST from Arduino client
        - If weatherLog.JSON does not exist:
            - Create empty weatherLog.JSON file
        - Read in weatherLog.JSON
        - Append POST body to JSON object
        - Write new JSON to weatherLog.JSON