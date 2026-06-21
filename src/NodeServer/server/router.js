/**
 * router.js
 * @author Jordan Locke
 * @version 0.1
 * @brief Recieves a request and finds the request handle and calls appropriate handler. If none found, responds to client with 404 error
 */

"using strict"

function route(req, res, handle, pathname){

    //Extracting router prefex to get route
    var pathParts = pathname.split('/');
    var route = '/' + pathParts[1];

    //Access handle at index route, let request handlers handle rest of URL path
    if(typeof handle[route] === 'function'){
        handle[route](req, res, pathname);
    } else {
        res.writeHead(404, {'Content-Type' : 'text/plain'});
        res.write("Error at Router - Resource Not Found");
        res.end();
    }
}

exports.route = route;