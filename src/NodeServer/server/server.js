/**
 * @author Jordan Locke
 * @version 0.1
 * @brief A simple web server to develop understanding of Web Development, JavaScript, and Node JS.
 *        This web server will eventually serve a webpage / web application to client browsers, and receieve information from the Arduino weather station
 * 
 * @author Jordan Locke
 * @version 0.2
 * Refactored for a more modular design. Serve now started via index.js, which calls this script to pass request to router function
 * 

 */
"use strict"

const http = require('http');
const url = require('url');

const port = 8080;

function startServer(route, handle){
    console.log('Starting Weather Web Server');
    http.createServer((req, res) =>{
        var pathname = url.parse(req.url).pathname;

        route(req, res, handle, pathname);

        console.log("Request Pathname is: " + pathname);
    }).listen(port);
    console.log("HTTP Server is listening on Port: " + port);
    console.log("Process ID: " + process.pid);
}

exports.startServer = startServer;