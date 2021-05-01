



let sum = 0, cx = 0, cy = 0, radius = 0;







exports.createAPI = function (app) {
   return new RESTfulAPI(app);
};

class RESTfulAPI {

    constructor(app) {


        app.get("/", function (req, res) {

            res.render("list", {
                sum: sum,
                cx: cx,
                cy: cy,
                radius: radius
            });


        });


        app.get("/api/model", function (req, res) {
            let model_id = req.query.model_id;
            console.log(model_id);
            let settings = {model_id: 1, upload_time: "12321213321", status: "ready"};
            let isExistingModel = false;
            if (!isExistingModel) {
                res.status(404);
            } else {
                res.status(200);
            }
            console.log(JSON.stringify(settings));
            res.send(JSON.stringify(settings));

        });


        app.get("/api/models", function (req, res) {
            let models = [{model_id: 1, upload_time: "12321213321", status: "ready"}, {
                model_id: 2,
                upload_time: "12332113",
                status: "pending"
            }, {model_id: 3, upload_time: "321321", status: "ready"}];
            console.log(JSON.stringify(models));
            res.send(JSON.stringify(models));

        });


        app.post("/api/model", function (req, res) {
            console.log("Im in");
            let model_type = req.query.model_type;
            // let train_data = req.body.train_data;
            if (model_type === "regression") {
                console.log("regression");
            } else {
                console.log("hybrid");
            }
            let settings = {model_id: 1, upload_time: "12321213321", status: "ready"};
            console.log(JSON.stringify(settings));
            res.send(JSON.stringify(settings));


        });


        app.post("/api/anomaly", function (req, res) {
            let model_id = req.query.model_id;
            //let train_data = req.body.predict_data;
            console.log(model_id);
            let isDone = false;
            if (!isDone) {
                res.redirect("/api/model?model_id="+model_id);
                return;
            }
            let anomalies = {anomalies: {col_name_1: [10, 12], col_name_2: [11, 23]}, reason: "Any"};
            console.log(JSON.stringify(anomalies));
            res.send(JSON.stringify(anomalies));


        });


        app.post("/", function (req, res) {
            const x = parseInt(req.body.x);
            const y = parseInt(req.body.y);

            sum = x + y;
            let points = [{x: 0, y: 0}, {x: 10, y: 10}, {x: 20, y: 20}, {x: 50, y: 50}];
            cx = 1;
            cy = 2;
            radius = 3;

            res.set({
                model_id: 3,
                upload_time: "2021-04-30T17:31:50Z",
                status: "ready"
            });

            res.redirect("/");


            // if (req.body.list === "Work") {
            //   workItems.push(item);
            //   res.redirect("/work");
            // } else {
            //   items.push(item);
            //   res.redirect("/");
            // }
        });


        app.delete("/api/model", function (req, res) {
            let model_id = req.query.model_id;
            console.log(model_id);
            let isExistingModel = false;
            if (!isExistingModel) {
                res.status(404);
                console.log(JSON.stringify("Cannot Delete Model"));
                res.send(JSON.stringify("Cannot Delete Model"));
            } else {
                res.status(200);
                console.log(JSON.stringify("Successfully Deleted Model"));
                res.send(JSON.stringify("Successfully Deleted Model"));
                // delete model
            }


        });


        app.listen(9876, function () {
            console.log("Server started on port 9876");
        });
    }
}