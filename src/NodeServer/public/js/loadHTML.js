/**
 * loadHTML.js
 * @author Jordan Locke
 * @version 0.1
 * @brief Fetches HTML file to load into dynamic content section of web app
 */
"use strict"

async function getHTML(requestedPage){

    console.log("ATTEMPTING TO GET DYNAMIC HTML...");
    const contentArea = $('#displayContent');
    

    //Try to fetch requsted HTML file from server
    try{
        let res = await fetch(requestedPage);

        if(!res.ok){
            console.log("RESPONSE NOT OK");
            contentArea.text('Error - Unable to retrieve requested content');
            return;
        } else{
            console.log("LOADING DYNAMIC HTML");

            contentArea.html(await res.text());
        }
    }
    catch(err){
        console.error(err);
    }
    
}

export {getHTML};