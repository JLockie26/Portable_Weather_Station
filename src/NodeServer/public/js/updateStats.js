/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A front-end script that fetches most recent weather log from server and displays it to home page
 */
"use strict"

let updateInterval = null;

$(document).ready(() => {
    //Initialises the script but does nothing until function is called in loadPages.js
});

async function updateLiveWeather() {

    const tempStat = document.getElementById("tempStat");
    const humidStat = document.getElementById("humidStat");
    const pressStat = document.getElementById("pressStat");

    if(updateInterval) clearInterval(updateInterval);

    try {
        let response = await fetch('/handleLiveWeather');
        if(!response.ok) {
            console.log(response.status);
            tempStat.textContent = "Offline";
            humidStat.textContent = "Offline";
            pressStat.textContent = "Offline";
            return;
        }else{
            let data = await response.json();
            tempStat.textContent = data.temp;
            humidStat.textContent = data.humid;
            pressStat.textContent = data.press;
        }

        console.log("Live Data Loaded");
    } catch (err) {
        console.error(err);
        tempStat.textContent = "Offline";
        humidStat.textContent = "Offline";
        pressStat.textContent = "Offline";
    }

    updateInterval = setInterval(updateLiveWeather, 60000);

}

export {updateLiveWeather};