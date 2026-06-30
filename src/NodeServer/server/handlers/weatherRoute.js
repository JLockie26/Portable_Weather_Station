/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A script that routes Arduino POST requests
 * 
 * @todo
 * - Consider a better sorting system to take in more data, for now, could use multiple JSON files for different years, or simply move straight to a database
 */
"use strict"
const { collectRequestBody, appendWeatherFile } = require('../utils/requestParser');

//Handles the routing for Arduino weather submissions
async function handleWeatherPost(req, res) {
    try {
        //Collect data from request body and store in JSON file (will migrate to database in future updates)
        const body = await collectRequestBody(req);
        await appendWeatherFile(body);

        //Log data for debugging, respond to Arduino client accordingly
        console.log("Arduino Data:", body);

        res.writeHead(200, {'Content-Type' : 'text/plain' });
        res.end("Data Recieved");
    } catch (err) {
        console.error(err);
        res.writeHead(400);
        res.end("Bad Request: ", err);
    }
}

module.exports = { handleWeatherPost };