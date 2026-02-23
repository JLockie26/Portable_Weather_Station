/**
 * @author Jordan Locke
 * @version 1.0
 * @brief A script that handles any static files the client may request (html, css, js for now)
 */

const path = require('path');
const fs = require('fs').promises;

async function serveStatic(req, res, serverRoot) {
    //Check request is GET only and not an API call
    if(req.method !== "GET" || req.url.startsWith("/api/")) return false;

    //Map URL to file inside ./public (Where the static files live)
    const filePath = path.join(serverRoot, "public", req.url === "/" ? "index.html": req.url);

    //Try read file path and set content type based on extension
    try {
        const file = await fs.readFile(filePath);

        const ext = path.extname(filePath);
        console.log(ext);
        const contentTypes = {
            ".html": "text/html",
            ".css": "text/css",
            ".js": "application/javascript"
        };

        res.writeHead(200, {'Content-Type': contentTypes[ext] || 'text/plain'});
        res.end(file);
        return true;
    } catch (err) { //Catch and respond with "File Not Found"
        res.writeHead(404);
        res.end("File Not Found");
        console.error(err);
        return true;
    }
}

module.exports = {serveStatic};