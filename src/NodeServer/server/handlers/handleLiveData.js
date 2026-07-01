/**
 * @author Jordan Locke
 * @version 0.1
 * @brief A script that handles  the request for live data (the most recent log from weatherLog.json)
 * 
 * @author Jordan Locke
 * @version 0.2
 * @brief Refactored to follow same standards as newer handlers
 */
"use strict"

const fs = require('fs').promises;
const resMsg = require('../utils/resMsg').resMsg;
const { readWeatherFile } = require('../utils/requestParser');

async function handleLiveWeather(req, res, pathname) {
    console.log('HANDLE LIVE WEATHER');
    const path = "server/data/weatherLog.json";
    await fs.mkdir("server/data/", {recursive: true}); //Ensure that directory exists

    //Try to read in weather log and respond with latest log. If any error occurs, send undefined rather than redirecting from home page
    try {
        const weatherLogJSON = await readWeatherFile(path);
        res.writeHead(200, {'Content-Type' : 'application/json'});
        res.end(JSON.stringify(weatherLogJSON[weatherLogJSON.length - 1]));
        console.log("JSON sent to client");
    } catch (err) {
        console.error(err);
        resMsg(res, 500, 'Weather Station Offline');
    }
}

module.exports = { handleLiveWeather };