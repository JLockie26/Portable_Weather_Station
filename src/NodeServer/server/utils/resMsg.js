//Small function to automate sending status messages to client
"use strict"
function resMsg(res, code, msg){
    res.writeHead(code, {'Content-Type' : 'text/html'});
    res.write(msg);
    res.end();
}

exports.resMsg = resMsg;