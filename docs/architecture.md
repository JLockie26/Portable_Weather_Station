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
6. End loop

## WeatherRecord Struct
A data structure that will aggregate all sensor data to be stored, displayed, and later transmitted. Structure will be active and in use next iteration.
- ambAirTemp: A float to store temperature in degrees celcius
- humidity: A float to store humidity %
- pressureHpa: A float to store air pressure in hectopascals
- weatherDate: A Date object to store logged date
- weatherTime: A Time object to store logged time

# Class Dictionary

## Date
### Overview
A class that holds values symbolising a date in DD/MM/YYYY format.
### Public Member Functions
- 'Date()' Default constructor for date object.
- 'Date(int newDay, int newMonth, int newYear)' Paramaterized constructor for date object.
- 'const Date& operator=(const Date &otherDate)' An overloaded assignment operator that assigns the values of another date to this date.
- 'void setDay(int newDay)' Sets day.
- 'int getDay() const' Gets day value.
- 'void setMonth(int newMonth)' Sets month.
- 'int getMonth() const' Gets month value.
- 'void setYear(int newYear)' Sets year.
- 'int getYear() const' Gets year value.
### Private Member Functions
- 'bool checkLeapYear()' Checks the year value is a leap year.
- 'void daysInMonth()' Checks how many days are in a certain month.
- 'void illegalDay()' Called when the day value exceeds a certain month's day range.
### Private Attributes
- int day
- int month
- int year

## Time
### Overview
A class that holds values that symbolise time in HH:MM format.
### Public Member Functions
- 'Time()' Default constructor.
- 'Time(int newHr, int newMin)' Paramaterized constructor.
- 'const Time& operator=(const Time &otherTime)' Overloaded assignment operator that assigns values of another time object to this time.
- 'void setMin(int newMin)' Sets minute value.
- 'int getMin() const' Gets minute value.
- 'void setHr(int newHr)' Sets hour value.
- 'void getHr() const' Gets hour value.
### Private Member Functions
- 'void validate()' validates hour and minute values.
### Private Attributes
- int hours
- int mnutes