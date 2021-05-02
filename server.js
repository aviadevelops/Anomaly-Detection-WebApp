const restAPI = require(__dirname + "/RESTfulAPI.js");
const express = require("express");
const bodyParser = require("body-parser");
require("ejs")
const app = express();



app.set('view engine', 'ejs');
app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(express.static("public"));
app.use(express.json());

restAPI.createAPI(app);