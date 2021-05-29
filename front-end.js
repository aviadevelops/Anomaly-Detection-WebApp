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


let trainFile = null, testFile = null, model_type = "hybrid", chart, testFileData, trainFileData,
    testPointsDict, xValues, anomaliesDict;

function hybrid_clicked() {
    model_type = "hybrid";
}

function regression_clicked() {
    model_type = "regression";
}

function load_graph(feature) {


    let xDict = {};
    let data = [];
    let dataSeries = {type: "line"};
    let dataPoints = [];
    let anomaliesRangeArray = anomaliesDict[feature];
    let points = [], anomaliesPoints = [];
    let str = "";

    if (anomaliesRangeArray != null) {
        for (let j = 0; j < anomaliesRangeArray.length; j++) {
            let anomaliesRange = anomaliesRangeArray[j];
            for (let i = anomaliesRange[0]; i <= anomaliesRange[1]; i++) {
                xDict[i] = true;
            }
            let xStart = anomaliesRange[0], xEnd = anomaliesRange[1];
            str += xStart + "-" + xEnd + " ";
        }
    }

    for (let i = 0; i < testPointsDict[feature].length; i++) {
        if (xDict[i] === true) {
            anomaliesPoints.push({x: i, y: testPointsDict[feature][i]});
        }
        points.push({x: i, y: testPointsDict[feature][i]});
    }

    dataSeries.dataPoints = dataPoints;
    data.push(dataSeries);

    if (str === "") {
        str = "None";
    }

    let ctx = document.getElementById('myChart').getContext('2d');
    if (chart !== undefined) {
        chart.destroy();
    }

    chart = new Chart(ctx, {
        type: 'line',
        title: feature + ": X Axis - timesteps, Y Axis - Values",
        data: {
            labels: xValues,
            datasets: [{
                label: feature,
                data: points,
                borderColor: 'rgb(0, 0, 255)',
                order: 2
            },
                {
                    label: 'Anomalies in ' + feature + ", X Axis Ranges: " + str,
                    data: anomaliesPoints,
                    showLine: false,
                    borderColor: 'rgb(255, 0, 0)',
                    backgroundColor: [
                        'rgb(255, 0, 0)'
                    ],
                    order: 1

                }]
        }
    });
}


$(document).ready(function () {


    $("#loading_div").css('display', 'none');

    regression_clicked();

    // The event listener for the file upload
    document.getElementById('trainLoader').addEventListener('change', saveTrain, false);
    document.getElementById('testLoader').addEventListener('change', saveTest, false);

    $("#send_btn").click(function () {
        $('#lbl').text("Anomalies will appear here: ");
        if (trainFile != null && testFile != null) {
            $("#loading_div").css('display', 'block');
            $("#myChart").css('display', 'none');
            $('#features_list').empty();
            upload(trainFile, "Train");
            upload(testFile, "Test");
            trainFile = null;
            testFile = null;
            alert("Train and Test files have been uploaded successfully.");
        } else if (trainFile == null && testFile == null) {
            alert("Train and Test files are missing.");
        } else if (trainFile == null) {
            alert("Train file is missing.");
        } else {
            alert("Test file is missing.");
        }
    });

    $("#btn_upload_train").click(function () {
        $("#trainLoader").click();
    });

    $("#btn_upload_test").click(function () {
        $("#testLoader").click();
    });

    $("#features_list").change(function () {
        let feature = $(this).val();
        load_graph(feature);
    });

    function update_list(featuresDict) {
        $.each(featuresDict, function (i, item) {
            $('#features_list').append(new Option(item, item));
        });
    }

    function alignAnomalies(anomalies) {
        Object.keys(anomalies).forEach(feature => {
            let anomaliesRangeArray = anomalies[feature];
            for (let j = 0; j < anomaliesRangeArray.length; j++) {
                let anomaliesRange = anomaliesRangeArray[j];
                anomaliesRange[0]--;
                anomaliesRange[1]--;
            }
        });
    }

    function upload(file, type) {
        let data = null;
        let reader = new FileReader();
        reader.readAsText(file);
        reader.onload = function (event) {
            let csvData = event.target.result;
            data = $.csv.toArrays(csvData);
            if (data && data.length > 0) {
                let req_url = "";
                if (type === "Train") {
                    req_url = 'http://localhost:8080/api/model?model_type=' + model_type;
                    trainFileData = data;
                }
                if (type === "Test") {
                    req_url = 'http://localhost:8080/api/anomaly';
                    testFileData = data;
                }
                $.ajax({
                    url: req_url,
                    type: 'post',
                    dataType: 'json',
                    contentType: 'application/json',
                    success: function (data) {
                        if (req_url.includes("anomaly")) {
                            xValues = [];
                            anomaliesDict = data;
                            testPointsDict = csvJSON(createCSVString(testFileData));
                            $("#loading_div").css('display', 'none');
                            $("#myChart").css('display', 'block');
                            for (let i = 0; i < testPointsDict[Object.keys(testPointsDict)[0]].length; i++) {
                                xValues.push(i);
                            }
                            alignAnomalies(data);
                            let parsedData = "Anomalies: ";
                            Object.keys(data).forEach(feature => {
                                let anomaliesRangeArray = data[feature];
                                parsedData += feature + ": ";
                                for (let j = 0; j < anomaliesRangeArray.length; j++) {
                                    let anomaliesRange = anomaliesRangeArray[j];
                                    parsedData += anomaliesRange[0] + "-" + anomaliesRange[1] + " ";
                                    if(j !== anomaliesRangeArray.length-1 ){
                                        parsedData += ", ";
                                    }
                                }
                            });
                            $('#lbl').text(parsedData);
                            $.ajax({
                                url: 'http://localhost:8080/api/features',
                                type: 'get',
                                dataType: 'json',
                                contentType: 'application/json',
                                success: function (data) {
                                    update_list(data);
                                    load_graph(Object.keys(testPointsDict)[0]);
                                }
                            });
                        }
                    },
                    data: JSON.stringify(csvJSON(createCSVString(data)))
                });
            }
        };
        reader.onerror = function () {
            alert('Unable to read ' + file.fileName);
        };
    }

// Method that reads and processes the selected file
    function saveTrain(evt) {
        trainFile = evt.target.files[0];
    }

// Method that reads and processes the selected file
    function saveTest(evt) {
        testFile = evt.target.files[0];
    }
});


















