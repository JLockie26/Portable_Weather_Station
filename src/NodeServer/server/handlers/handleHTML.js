/**
 * handleHTML.js
 * @author Jordan Locke
 * @version 0.1
 * @brief Handles incoming HTML requests for single page style of loading content
 */
"use strict"
const fs = require('fs');
const path = require('path');

function reqHTML(req, res, pathname){
    //parse pathname to get file name
    const decodedPath = decodeURIComponent(pathname);
    const filePath = path.join('./public', decodedPath);
    const ext = path.extname(filePath).toLowerCase();

    console.log("HANDLE HTML - Serving: " + filePath);

    if(ext === '.html'){
        fs.readFile(filePath, (err, data)=>{
            if(err){
                console.error(err);
                res.writeHead(400, {'Content-Type' : 'text/plain'});
                res.write("HTML ERROR - CANNOT LOCATE: " + filePath + '\n');
                res.end();
            } else {
                //Respond to client by serving file
                res.writeHead(200, {'Content-Type' : 'text/html'});
                res.end(data);
            }
        });
    }else{ //If file is not JavaScript, do not read in file
        res.writeHead(415, {'Content-Type' : 'text/plain'});
        res.write('HTML ERROR - UNSUPPORTED EXTENSION TYPE');
        res.end();
    }
}

exports.reqHTML = reqHTML;