/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A simple web server to develop understanding of Web Development, JavaScript, and Node JS.
 *        This web server will eventually serve a webpage / web application to client browsers, and receieve information from the Arduino weather station
 */

const http = require('http');
const {serveStatic} = require('./routes/staticFiles');
const { handleWeatherPost } = require('./routes/weatherRoute');
const { handleLiveWeather } = require('./routes/liveDataRoute');
const port = 8080;
const serverRoot = __dirname;

const server = http.createServer(async function(req, res) {
    //GET request for home page and all static files needed
    if(await serveStatic(req, res, serverRoot)) return;
    //POST data from Arduino to server
    else if(req.method === "POST" && req.url === "/api/weather/")
    {
        return handleWeatherPost(req, res);   
    }
    else if(req.method === "GET" && req.url === "/api/live-weather/")
    {
        return handleLiveWeather(res);
    }
    else {
        res.writeHead(404, {'Content-Type' : 'text/plain'});
        res.end("Not Found");
    }

});

server.listen(port, function(error){
    if(error) {
        console.log("An error occured", error);
    } else {
        console.log("Sever is listening on port " + port);
    }
});