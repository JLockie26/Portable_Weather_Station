/**
 * handleImg.js
 * @author Jordan Locke
 * @version 0.2
 * @brief Handles incoming requests for image files
 * 
 * @todo
 * Change responding method from readstream to readfile. Should not need to pipe static images that would be changed again
 */
"use strict"
const fs = require('fs');
const path = require('path');

function reqImg(req, res, pathname){
    
    //parse pathname to get file name
    const decodedPath = decodeURIComponent(pathname);
    const filePath = path.join('./public', decodedPath);
    const ext = path.extname(filePath).toLowerCase();

    console.log("HANDLE IMG - Serving: " + filePath);

    let contentType;

    switch(ext){
        case ".png":
            contentType = "image/png";
            break;
        
        case ".jpg":
            contentType = "image/jpeg";
            break;

        case ".gif":
            contentType = "image/gif"
            break;
        
        default:
            res.writeHead(415, {'Content-Type' : 'text/plain'});
            res.write('IMG ERROR - UNSUPPORTED EXTENSION TYPE');
            res.end();
            return;
    }
    
    //create a readstream for image and serve to client
    const readStream = fs.createReadStream(filePath);
    readStream.on('open', () => {
        res.writeHead(200, {'Content-Type': + contentType});
        readStream.pipe(res);
    });
    readStream.on('error', () =>{
        res.writeHead(404, {'Content-Type' : 'text/plain'});
        res.write("IMG ERROR - CANNOT LOCATE: " + filePath + '\n');
        res.end();
    });

}

exports.reqImg = reqImg;