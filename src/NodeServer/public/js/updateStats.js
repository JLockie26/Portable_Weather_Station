/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A front-end script that fetches most recent weather log from server and displays it to home page
 */

const tempStat = document.getElementById("temp-stat");
const humidStat = document.getElementById("humid-stat");
const pressStat = document.getElementById("press-stat");

async function updateLiveWeather() {
    try {
        let response = await fetch('/api/live-weather/');
        if(!response.ok) {
            console.log("Some Error Occured");
            tempStat.textContent = "Offline";
            humidStat.textContent = "Offline";
            pressStat.textContent = "Offline";
            return;
        }

        let data = await response.json();
        tempStat.textContent = data.temp;
        humidStat.textContent = data.humid;
        pressStat.textContent = data.press;

        console.log("Live Data Loaded");
    } catch (err) {
        console.error(err);
    }
}

//Request weather every 1 minute
setInterval(updateLiveWeather, 60000);
updateLiveWeather();