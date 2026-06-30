/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A script to parse request body 
 */
"use strict"
const fs = require('fs').promises;

function collectRequestBody(req) {
    return new Promise((resolve, reject) => {
        let body = "";

        req.on("data", weatherChunk => {
            body += weatherChunk.toString();
        });

        req.on("end", () => {
            resolve(body);
        });

        req.on("error", reject);
    });
}

async function appendWeatherFile(body) {
    const path = "./data/weatherLog.json";
    await fs.mkdir("./data", {recursive: true}); //Ensure that directory exists
    let bodyJSON;

    //Check if file exists, create file if not then read
    await checkFileExists(path);
    const weatherJSON = await readWeatherFile(path);
    
    //Validate request body input
    try {
        bodyJSON = JSON.parse(body);
    } catch(err) {
        throw new Error("Invalid JSON body");
    } 

    //Validate request body structure
    if(typeof bodyJSON.temp !== "number" || typeof bodyJSON.humid !== "number")
        throw new Error("Invalid weather payload");

    weatherJSON.push(bodyJSON);
    
    //Write updated JSON file to directory
    await writeWeatherFile(path, weatherJSON);

    return bodyJSON;
}

async function checkFileExists(path) {
    try {
        await fs.access(path);
    } catch (err) {
        if(err.code === "ENOENT"){ //Specific code for file not found
            console.log("File Does Not Exist");
            const defaultContent = "[]"; //Ensures that JSON object is an array when read in
            await fs.writeFile(path, defaultContent, "utf8");
        } else {
            throw err;
        }
    }
}


//Encapsulated read/write functions
async function readWeatherFile(path) {
    try {
        const data = await fs.readFile(path, "utf8");
        return JSON.parse(data);
    } catch (err) {
        throw err;
    }    
}

async function writeWeatherFile(path, dataObject) {
    const dataString = JSON.stringify(dataObject, null, 2);
    try {
        await fs.writeFile(path, dataString, "utf8");
    } catch (err) {
        throw err;
    }
}

module.exports = { collectRequestBody, appendWeatherFile, readWeatherFile };