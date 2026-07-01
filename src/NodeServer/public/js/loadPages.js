/**
 * @author Jordan Locke
 * @version 0.1
 * @brief Acts as a front-end router, fetching HTML files from server, and calling appropriate functions
 */
"use strict"

import { updateLiveWeather } from "./updateStats.js";

//Controller
$(document).ready(() => {

    //Listen for nav-button events
    $('.navBtn').click(function(){
        const requestedPage = $(this).attr('data-page');
        getHTML(requestedPage).then(() => {
            initialisePageScript($(this).attr('id'));
        }).catch((error) => {
            console.log(error);
        });
    })

});

//Fetch the HTML file of a certain page
async function getHTML(requestedPage){

    console.log("ATTEMPTING TO GET DYNAMIC HTML...");
    try{
        let res = await fetch(requestedPage);

        if(!res.ok){
            console.log("RESPONSE NOT OK");
            $('.displayContent').text(res.status + '-' + res.statusText);
            return;
        } else{
            console.log("LOADING DYNAMIC HTML");
            const html = await res.text();
            $('.displayContent').html(html);

            return Promise.resolve();
        }
    }
    catch(err){
        console.error(err);
    }
    
}

//Load certain scripts depending on what page was loaded (only required for live weather at the moment)
function initialisePageScript(btnID){
    
    switch(btnID){
        case 'liveWeather':
            console.log('Loading Live Weather Scripts');
            updateLiveWeather();
            break;
        case 'weatherHistory':
            console.log('Loading Weather History Scripts');
            break;
        case 'aboutApp':
            console.log('Loading About App Scripts');
            break;
        default:
            console.log('Unknown page, not running any scripts');
    }

}