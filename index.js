const anomalyDetector = require('./build/Release/anomalydetector.node');
const Model = require(__dirname + "/model.js");

console.log();


function getAnomalies() {
    let startingIndexesMap = anomalyDetector.getAnomalies();
    let anomaliesArray = [];
    Object.entries(startingIndexesMap).forEach(entry => {
        const [key, value] = entry;
        anomaliesArray.push([parseInt(key), value]);
    });
    return anomaliesArray;

}


anomalyDetector.createTrainTS("anomalyTrain.csv");
anomalyDetector.createTestTS("anomalyTest.csv");
anomalyDetector.learnNormal("regression");
anomalyDetector.detect();
console.log(anomalyDetector.getStatus());
console.log(getAnomalies());





let m = new Model.createModel(1, "ready");
console.log(JSON.stringify(m));