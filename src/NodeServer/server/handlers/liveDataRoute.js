/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A script that handles  the request for live data (the most recent log from weatherLog.json)
 */

const fs = require('fs').promises;
const { readWeatherFile } = require('../utils/requestParser');

async function handleLiveWeather(res) {

    const path = "./data/weatherLog.json";
    await fs.mkdir("./data", {recursive: true}); //Ensure that directory exists

    //Try to read in weather log and respond with latest log. If any error occurs, send undefined rather than redirecting from home page
    try {
        const weatherLogJSON = await readWeatherFile(path);
        res.writeHead(200, {'Content-Type' : 'application/json'});
        res.end(JSON.stringify(weatherLogJSON[weatherLogJSON.length - 1]));
        console.log("JSON sent to client");
    } catch (err) {
        const errorJSON = {temp: "undefined", humid: "undefined", press: "undefined"};
        res.writeHead(500);
        res.end(JSON.stringify(errorJSON));
        console.log("JSON not sent");
    }
}

module.exports = { handleLiveWeather };