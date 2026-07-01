/**
 * index.js - This script will be used to initiate the Node.js server for this project
 * @author Jordan Locke
 * @version 0.2
 * @brief Calls function to start server
 * 
 * @author Jordan Locke
 * @version 0.3
 * @brief A modular approach to starting web-server. Keeps a list of all potential handlers
 */
"use strict"

var server = require('./server/server');
var router = require('./server/router');

//Initialise handle object to determine where to found certain requests
var handle = {};

//Handling initial HTML page & static files
handle['/'] = require('./server/handlers/start').reqStart;
handle['/css'] = require('./server/handlers/handleCSS').reqCSS;
handle['/img'] = require('./server/handlers/handleImg').reqImg;
handle['/js'] = require('./server/handlers/handleJS').reqJS;
handle['/html'] = require('./server/handlers/handleHTML').reqHTML;
handle['/handleLiveWeather'] = require('./server/handlers/handleLiveData').handleLiveWeather;
//handle['/api/weather/'] = require('./server/handlers/weatherRoute').handleWeatherPost;

//Start server
server.startServer(router.route, handle);