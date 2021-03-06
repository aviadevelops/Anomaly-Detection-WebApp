const server = require(__dirname + "/server.js");
const Model = require(__dirname + "/model.js");


exports.createAPI = function (app) {
    return new RESTfulAPI(app);
};


function parseAnomalies(amomaliesMap) {
    let anomalies = {};
    Object.keys(amomaliesMap).forEach(columnName => {
        anomalies[columnName] = []
    });
    Object.entries(amomaliesMap).forEach(entry => {
        const [key, value] = entry;
        let span = [];
        Object.entries(value).forEach(entry => {
            const [key1, value1] = entry;
            span.push([parseInt(key1), value1]);
        });
        anomalies[key] = span;
    });
    return anomalies;

}

class RESTfulAPI {


    constructor(app) {


        app.get("/", function (req, res) {
            try{
                res.sendFile('index.html', {root: __dirname});
            }
            catch (error){}

        });


        app.get("/front-end.js", function (req, res) {
            try {
                res.sendFile('front-end.js', {root: __dirname})
            }
            catch (error){

            }

        });

        app.get("/api/model", function (req, res) {
            try {
                let isExistingModel = true;
                let model_id = req.query.model_id;
                let model = server.getModel(model_id);
                if (model === -1) {
                    isExistingModel = false;
                }
                if (!isExistingModel) {
                    res.status(404).send();
                    return;
                } else {
                    res.status(200);
                }
                res.send(JSON.stringify(Model.getJson(model)));
            }
            catch (error){

            }


        });


        app.get("/api/models", function (req, res) {
            try{ res.send(JSON.stringify(server.getModels()));}
            catch (error){

            }


        });

        app.get("/api/features", function (req, res) {
            try {
                let model = server.getModel(1);
                res.send(JSON.stringify(model.getFeatures()));
            }
            catch (error){

            }


        });


        app.post("/api/model", function (req, res) {
            try{
                let model_type = req.query.model_type;
                let model = server.getReadyModel();
                model.createTrainTS(req.body); // need to get the csv first
                if (model_type === "regression") {
                    model.learnNormal("regression");
                } else {
                    model.learnNormal("hybrid");
                }
                model.updateStatus();
                res.send(JSON.stringify(Model.getJson(model)));
            }
            catch (error){
                res.redirect("/");
            }



        });


        app.post("/api/anomaly", function (req, res) {
            try {
                let model_id = 1;
                let model = server.getModel(model_id);
                model.createTestTS(req.body);
                model.detect();
                model.updateStatus();
                let isDone = false;
                if (model.status === "ready") {
                    isDone = true;
                }
                if (!isDone) {
                    res.redirect("/api/model?model_id=" + model_id);
                    return;
                }
                let anomalies = parseAnomalies(model.getAnomalies());
                res.send(JSON.stringify(anomalies));
            }
            catch (error){
                res.redirect("/");
            }

        });


        app.delete("/api/model", function (req, res) {
            try{
                let model_id = req.query.model_id;
                let model = server.getModel(model_id);
                let isExistingModel = model !== -1;
                if (!isExistingModel) {
                    res.status(404);
                    console.log(JSON.stringify("Cannot Delete Model"));
                    res.send(JSON.stringify("Cannot Delete Model"));
                } else {
                    res.status(200);
                    server.deleteModel(model_id);
                    console.log(JSON.stringify("Successfully Deleted Model"));
                    res.send(JSON.stringify("Successfully Deleted Model"));
                    // delete model
                }
            }
            catch (error){

            }

        });


        app.listen(8080, function () {
            console.log("Server started on port 8080");
        });
    }
}