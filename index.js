const anomalyDetector = require('./build/Release/anomalydetector.node');
const Model = require(__dirname + "/model.js");
const CSV = require('csv-string');



console.log();


function getAnomalies() {
    let startingIndexesMap = anomalyDetector.getAnomalies();
    //console.log(startingIndexesMap);
    let anomalies = {};

    Object.keys(startingIndexesMap).forEach(columnName=>{anomalies[columnName]=[]});
     Object.entries(startingIndexesMap).forEach(entry => {
        const [key, value] = entry;
        let span =[];
        Object.entries(value).forEach(entry => {
            const [key1, value1] = entry;
            span.push([parseInt(key1),value1]);
        });
         anomalies[key] = span;
    });
    return anomalies;

}

function csvJSON(csv) {
    const lines = csv.split('\n')
    const result = []
    const obj = {}
    const headers = lines[0].split(',')
    for (let j = 0; j < headers.length; j++) {
        obj[headers[j]]=[];
    }
    for (let i = 1; i < lines.length; i++) {
        if (!lines[i])
            continue

        const currentline = lines[i].split(',')

        for (let j = 0; j < headers.length; j++) {
            obj[headers[j]].push(currentline[j]);
        }

    }
    return obj;
}

let parsedJson = {"altitude_gps":[
        100, 110, 20, 120
    ],
    "heading_gps":[
        0.6,0.59,0.54, 0.51
    ]};


const fs = require('fs')

let dataTrain = csvJSON(fs.readFileSync("anomalyTrain.csv", 'utf8'));
let dataTest = csvJSON(fs.readFileSync("anomalyTest.csv", 'utf8'));







// console.log(data)
anomalyDetector.createTrainTS(dataTrain);
anomalyDetector.createTestTS(dataTest);
anomalyDetector.learnNormal("hybrid");
anomalyDetector.detect();
console.log(anomalyDetector.getStatus());
let anomalies = getAnomalies();
let json = {anomalies: anomalies, reason: "Sig"};
console.log(JSON.stringify(json));










console.log(1!==1);

