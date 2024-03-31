const express = require("express");
const http = require('http');
const https = require('https');
const nunjucks = require("nunjucks");
const fs = require('fs');
const readline = require('readline');



const app = express();
const httpPort = 8080;
/*const httpsPort = 8443;
const key = fs.readFileSync(__dirname + '/selfsigned.key');
const cert = fs.readFileSync(__dirname + '/selfsigned.crt');
const options = {
	key: key,
	cert: cert
};*/

app.engine("html", nunjucks.render);
app.set("view engine", "html");
app.use(express.static("public"));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

process.stdin.setDefaultEncoding('utf8');

nunjucks.configure(".", {
    autoescape: true,
    express: app,
});

app.get("/", (request, response) => {
    response.render("index");
});

app.get("/index.html", (request, response) => {
    response.render("index");
});

app.get("/index.js", (request, response) => {
    response.sendFile(__dirname + "/index.js");
});

app.get("/arduino_lib.js", (request, response) => {
    response.sendFile(__dirname + "/arduino_lib.js");
});

app.get("/style.css", (request, response) => {
    response.sendFile(__dirname + "/style.css");
});

app.post("/api/set-pin-state", (request, response) => {
    process.stderr.write("POST event detected" + JSON.stringify(request.body) + '\n');
    request.body.type = "command";
    request.body.command = "set-pin-state";
    process.stdout.write(JSON.stringify(request.body));
    process.stdin.once('data', function (data) {
        process.stderr.write('Recieved from C++: ' + data + '\n');
        response.status(200).send(data);
    });
});

app.post("/api/get-pin-state", (request, response) => {
    process.stderr.write("POST event detected" + JSON.stringify(request.body) + '\n');
    request.body.type = "command";
    request.body.command = "get-pin-state";
    process.stdout.write(JSON.stringify(request.body));
    process.stdin.once('data', function (data) {
        process.stderr.write('Recieved from C++: ' + data + '\n');
        response.status(200).send(data);
    });
});

app.post("/api/config-pin-mode", (request, response) => {
    process.stderr.write("POST event detected" + JSON.stringify(request.body) + '\n');
    request.body.type = "command";
    request.body.command = "config-pin-mode";
    process.stdout.write(JSON.stringify(request.body));
    process.stdin.once('data', function (data) {
        process.stderr.write('Recieved from C++: ' + data + '\n');
        response.status(200).send(data);
    });
});



let httpServer = http.createServer(app);
//let httpsServer = https.createServer(options, app);

httpServer.listen(httpPort, () => {
	process.stderr.write(`Your local http server is waiting for requests at 127.0.0.1:${httpPort} or at localhost:${httpPort}\n`);
});

/*httpsServer.listen(httpsPort, () => {
    process.stderr.write(`Your local https server is waiting for requests at 127.0.0.1:${httpsPort} or at localhost:${httpsPort}\n`);
});*/
