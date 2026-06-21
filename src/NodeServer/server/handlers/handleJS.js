/**
 * handleJS.js
 * @author Jordan Locke
 * @version 0.1
 * @brief Handles incoming requests for JavaScript files
 * Extra security may be required for this section
 */
"use strict"
const fs = require('fs');
const path = require('path');

function reqJS(req, res, pathname){
    //parse pathname to get file name
    const decodedPath = decodeURIComponent(pathname);
    const filePath = path.join('./public', decodedPath);
    const ext = path.extname(filePath).toLowerCase();

    console.log("HANDLE JS - Serving: " + filePath);

    if(ext === '.js'){
        fs.readFile(filePath, (err, data)=>{
            if(err){
                console.error(err);
                res.writeHead(400, {'Content-Type' : 'text/plain'});
                res.write("JS ERROR - CANNOT LOCATE: " + filePath + '\n');
                res.end();
            } else {
                //Respond to client by serving file
                res.writeHead(200, {'Content-Type' : 'text/javascript'});
                res.write(data);
                res.end();
            }
        });
    }else{ //If file is not JavaScript, do not read in file
        res.writeHead(415, {'Content-Type' : 'text/plain'});
        res.write('JS ERROR - UNSUPPORTED EXTENSION TYPE');
        res.end();
    }
}

exports.reqJS = reqJS;