// const anomalyDetector = require('./build/Release/anomalydetector.node');
// const Model = require(__dirname + "/model.js");
// const CSV = require('csv-string');
// const fs = require('fs')
//
//
// function getAnomalies() {
//     let startingIndexesMap = anomalyDetector.getAnomalies();
//     //console.log(startingIndexesMap);
//     let anomalies = {};
//
//     Object.keys(startingIndexesMap).forEach(columnName => {
//         anomalies[columnName] = []
//     });
//     Object.entries(startingIndexesMap).forEach(entry => {
//         const [key, value] = entry;
//         let span = [];
//         Object.entries(value).forEach(entry => {
//             const [key1, value1] = entry;
//             span.push([parseInt(key1), value1]);
//         });
//         anomalies[key] = span;
//     });
//     return anomalies;
//
// }
//
// function csvJSON(csv) {
//     const lines = csv.split('\n')
//     const result = []
//     const obj = {}
//     const headers = lines[0].split(',')
//     for (let j = 0; j < headers.length; j++) {
//         obj[headers[j]] = [];
//     }
//     for (let i = 1; i < lines.length; i++) {
//         if (!lines[i])
//             continue
//
//         const currentline = lines[i].split(',')
//
//         for (let j = 0; j < headers.length; j++) {
//             obj[headers[j]].push(currentline[j]);
//         }
//
//     }
//     return obj;
// }
//
//
// function selectFeature() {
//     let featuresList = document.getElementById("featuresList");
//
// }
//
// function buttonClick() {
//     let dataTrain = csvJSON(fs.readFileSync("anomalyTrain.csv", 'utf8'));
//     let dataTest = csvJSON(fs.readFileSync("anomalyTest.csv", 'utf8'));
//
//
// // console.log(data)
//     anomalyDetector.createTrainTS(dataTrain);
//     anomalyDetector.createTestTS(dataTest);
//     anomalyDetector.learnNormal("hybrid");
//     anomalyDetector.detect();
//
//
//     let anomalies = getAnomalies();
//     let json = {anomalies: anomalies, reason: "Sig"};
//     console.log(JSON.stringify(json));
//
//
//
//     let features = anomalyDetector.getFeatures();
//     let featuresArray = [];
//     Object.entries(features).forEach(entry => {
//         const [key, value] = entry;
//         featuresArray.push(value);
//     });
//
//     let featureList = document.getElementById("featuresList");
//      let b = document.getElementById("arthur")
//
//     for (let i = 0; i < featuresArray.length; i++) {
//         b.innerText = featuresArray[i];
//         let option = document.getElementById("option");
//         option.text = featuresArray[i];
//         featureList.add(option);
//     }
//
//
// }
//
// function addFeature(feature) {
//     var sel = document.getElementById('featuresList');
//
// // create new option element
//     var opt = document.createElement('option');
//
// // create text node to add to option element (opt)
//     opt.appendChild(document.createTextNode(feature));
//
// // set value property of opt
//     opt.value = 'option value';
//
// // add opt to end of select box (sel)
//     sel.appendChild(opt);
// }
//
//
//
//
//
//

function createCSVString(data) {
    let str = ""
    for (let i = 0; i < data.length; i++) {
        let line = data[i];
        for (let j = 0; j < line.length; j++) {
            str += line[j];
            if (j < line.length - 1)
                str += ",";
        }
        if (i < data.length - 1)
            str += "\n";
    }
    return str;
}

function csvJSON(csv) {
    const lines = csv.split('\n')
    const obj = {}
    const headers = lines[0].split(',')
    for (let j = 0; j < headers.length; j++) {
        obj[headers[j]] = [];
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


$(document).ready(function () {
    // The event listener for the file upload
    document.getElementById('trainLoader').addEventListener('change', uploadTrain, false);
    document.getElementById('testLoader').addEventListener('change', uploadTest, false);
    function upload(evt, s) {
        // if (s === "train") {
        //     console.log("train");
        // } else {
        //     console.log("test");
        // }
        var data = null;
        var file = evt.target.files[0];
        var reader = new FileReader();
        reader.readAsText(file);
        reader.onload = function (event) {
            var csvData = event.target.result;
            data = $.csv.toArrays(csvData);
            if (data && data.length > 0) {
                if (s === "train") {
                    $.post('http://localhost:9876/api/model?model_type=hybrid',
                        {
                            json: csvJSON(createCSVString(data))
                        },
                        function (error, response, body) {
                            // console.log(error);
                            // console.log(response);
                            console.log(body);
                            res.send(body);
                        });
                }
                if (s === "test") {

                }

            }
        };
        reader.onerror = function () {
            alert('Unable to read ' + file.fileName);
        };
    }

    // Method that reads and processes the selected file
    function uploadTrain(evt) {
        upload(evt, "train");

    }

    // Method that reads and processes the selected file
    function uploadTest(evt) {
        upload(evt, "test");

    }
});


















