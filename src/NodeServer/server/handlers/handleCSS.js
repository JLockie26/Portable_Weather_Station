/**
 * handleCss.js
 * @author Jordan Locke
 * @version 0.1
 * @brief Handles incoming requests for CSS files
 */
"use strict"
const fs = require('fs');
const path = require('path');

function reqCSS(req, res, pathname){
    
    //parse pathname to get file name
    const decodedPath = decodeURIComponent(pathname);
    const filePath = path.join('./public', decodedPath);
    const ext = path.extname(filePath).toLowerCase();

    console.log("HANDLE CSS - Serving: " + filePath);

    //Read file in
    if(ext === '.css'){
        fs.readFile(filePath, (err, data) =>{
            if(err){
                console.error(err);
                res.writeHead(400, {'Content-Type' : 'text/plain'});
                res.write("CSS ERROR - CANNOT LOCATE: " + filePath + '\n');
                res.end();
            } else {
                //Respond to client by serving file
                res.writeHead(200, {'Content-Type' : 'text/css'});
                res.write(data);
                res.end();
            }
        });
    } else{ //If file is not CSS, do not read in file
        res.writeHead(415, {'Content-Type' : 'text/plain'});
        res.write('CSS ERROR - UNSUPPORTED EXTENSION TYPE');
        res.end();
    }
    

}

exports.reqCSS = reqCSS;