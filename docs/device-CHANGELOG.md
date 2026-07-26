
# Weather Station Change Log
All notable changes to the Weather Station part of this project will be documented in this file.
 
The format is based on [Keep a Changelog](http://keepachangelog.com/).
 
## [0.6]
 
- User will need to provide their own wifi_secrets.h and sever_secrets.h files
- Assumed that user is connecting to a WPA/WPA2 network
 
### Added
- Implemented WiFiS3 library
- Implemented functions to handle local network connection and data transfer over HTTP
 
### Changed
- Refactored setup to attempt network connection
- Refactored loop to connect to server if local connection is established
 
## [0.5]
 
### Added
- State machine implemented to help timing of measurements and logging data.
 
### Changed
- Temporarily removed OLED functionality to stop BMP interference.
- Reinstated OLED functionality after fixing bug
 
### Fixed
- I2C conflict bug. All components seem to work when running at 3.3v instead of 5v
 
## [0.4]
   
### Changed
- Changed graphics library so OLED screen isn't hogging Serial Data Line
- Modified main logic so weather is only being collected, displayed, and logged every 5 mins.
 
### Fixed
- Attempted fix at conflicts with I2C devices (BMP sensor & OLED Screen)

## [0.3]
 
### Added
- Implemented SD card writing
 

## [0.2]
 
### Added
- Functions for collecting and displaying weather data
   
### Changed
- Modularised functionality into separate header and definition files
 

## [0.1]
 
### Added
- Initial sketch creation for a portable weather station project

- This project is intended as an extension of a university assignment and a personal challenge to hone programming skills and learn electronics.
- The purpose of this sketch is to initialise all pins and sensors connected to the Arduino before calling separate-
C++ modules to collect, store, and display weather data.