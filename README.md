# Portable Arduino Weather Station

An Arduino-based weather station and web application for recording local weather, displaying live metrics, and visualizing recorded measurements. The weather station component uses an Arduino sensor kit and open-source libraries to introduce myself to the concept of embedded systems and electronics. The web application component of this project uses a HTML/CSS/JS & Node.js stack for asynchronous handling and to streamline development with JavaScript. For now, no frameworks have been used for the web app. This is to keep the focus on the interaction between the application and weather station.

Goals of this repository:
- Dive into basic concepts of embedded systems
- Expand knowledge about system integration and interoperability
- Produce a system that can be easily deployed into an environment (i.e. backyard or window sill)

## Technologies Used
### Arduino Device (C/C++)
- Arduino Uno R4 WiFi
- Arduino Sensor Kit or the following sensors:
    - [Grove Base Shield](https://wiki.seeedstudio.com/Base_Shield_V2/)
    - [Grove DHT11 Sensor](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)
    - [Grove BMP280 Sensor](https://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP280/)
    - [Grove OLED Display 0.96 inch](https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/)
    - [XC4386 SD Card Module](https://media.jaycar.com.au/product/resources/XC4386_manualMain_78737.pdf)

### Web App
- Node.js
- JSON file storage
- HTML, CSS, Javascript

## Features
- Reads temperature(Celsius), humidity, and air pressure(Hectopascals).
- Stores measurements in appropriate data structure
- Display current measurements to OLED screen
- Sends data via HTTP POST to a Node.js server
- Stores data in SD card in event of connection failure
- Stores readings in a JSON log file
- Serves a basic frontend for viewing live readings (reading history WIP)

Learn how to set up the project [here](./docs/projectsetup.md)

## The Process
This project initially started as a tinkering project. I purchased an Arduino kit from a local electronics shop to learn more about electronics and how code interacts with hardware at a lower level.
The original goal was to build a self contained system, that would display and store weather measurements. After learning more about web development, I decided to revise the goal to send data to a web server wirelessly.

Early commits showcase the learning process of programming an Arduino, especially communicating with other sensors, displaying and logging measurements, and setting up timing so the device was functional on its own.

After the device was working independently, I began working on the web server and WiFi connectivity for the weather station.

--Project still in progress--

## What I have Learnt
- To be added

## Live Demo
- To be filmed & uploaded

## Project Status
**Current Iteration** 

WebApp v0.2

Weather Station v0.6

**Status:** Active Development


## Architecture Overview

Arduino -> HTTP POST -> Node.js Server -> JSON Storage -> Frontend Fetch request to Client (Visual Diagram in Progress)

## Current Limitations
- Race conditions exist. If timed right, server may not update live weather.
- No Database usage
- Limited to no API authentication or rate limiting
- Minimal client-side and server-side validation
- Past weather logs not displayed yet
- Local network functionality only

## Roadmap

- Weather station code clean up
- Refactor SD card and OLED screen usage
- Improve client and server validation and security
- Implement structured logging & data visualization