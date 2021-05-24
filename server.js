const restAPI = require(__dirname + "/RESTfulAPI.js");
const express = require("express");
const bodyParser = require("body-parser");
const Model = require(__dirname + "/model.js");
require("ejs")
const app = express();


app.set('view engine', 'ejs');
app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(express.static("public"));

restAPI.createAPI(app);

let dict = {};
let m1 = new Model.createModel(1), m2 = new Model.createModel(2), m3 = new Model.createModel(3);
dict[m1.model_id] = m1;
dict[m2.model_id] = m2;
dict[m3.model_id] = m3;
console.log(dict);
console.log(Object.keys(dict).length);

exports.getModel = function (id) {
    if (!(id in dict)) {
        return -1;
    }
    return dict[id];
};

exports.getModels = function () {
    let models = [];
     Object.values(dict).forEach(model => {
         models.push(Model.getJson(model));
     });
     return models;
};

exports.getReadyModel = function () {
    let isFoundExistingModel = false, modelFound;
    let model;
    for (let id=1; id<=Object.keys(dict).length;id++){
        model = dict[id];
        if(model.status==="ready"){
            isFoundExistingModel = true;
            modelFound = model;
            break;
        }
    }
    if (isFoundExistingModel===true){
        return modelFound;
    }
    let id = Object.keys(dict).length+1;
    modelFound = Model.createModel(id);
    dict[modelFound.id] = modelFound;
    return modelFound;
};

exports.deleteModel = function (id) {
    delete dict[id];
};



