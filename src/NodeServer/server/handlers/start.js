/**
 * start.js
 * @author Jordan Locke
 * @version 0.1
 * @brief Handles initial serving of client index page
 */

"use strict"
const fs = require('fs');

function reqStart(req, res, pathname){

    fs.readFile('./public/index.html', 'utf8', (err, data) =>{
        if(err){
            console.error(err);
            res.writeHead(404, {'Content-Type' : 'text/plain'});
            res.write("START ERROR - Cannot Locate Index File");
            res.end();
        } else {
            res.writeHead(200, {'Content-Type' : 'text/html'});
            res.write(data);
            res.end();
        }
});

}

exports.reqStart = reqStart;