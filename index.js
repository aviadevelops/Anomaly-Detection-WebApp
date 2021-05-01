const anomalyDetector = require( './build/Release/anomalydetector.node' );

console.log();


function getAnomalies() {
    let startingIndexesMap = anomalyDetector.getAnomalies();
    let anomaliesArray = [];
    Object.entries(startingIndexesMap).forEach(entry => {
        const [key, value] = entry;
        anomaliesArray.push([parseInt(key),value]);
    });
    return anomaliesArray;

}

console.log( anomalyDetector.getHello(1,2) );
console.log(anomalyDetector.getSig("Sig","Man"));
anomalyDetector.createTrainTS("anomalyTrain.csv");
anomalyDetector.createTestTS("anomalyTest.csv");
anomalyDetector.learnNormal();
anomalyDetector.detect();
console.log(getAnomalies());