exports.createModel = function (model_id) {
    return new Model(model_id);
};
exports.getJson = function (model) {
    return model.getJson();
}


class Model {

    constructor(model_id) {
        this.model_id = model_id;
        this.upload_time = this.getCurrentTime();
        this.status = "ready";

        this.anomalyDetector = require('./build/Release/anomalydetector.node');
    }

    getCurrentTime() {
        let currentdate = new Date();
        let offset = new Date().getTimezoneOffset(), o = Math.abs(offset);
        let timeZone = (offset < 0 ? "+" : "-") + ("00" + Math.floor(o / 60)).slice(-2) + "." + ("00" + (o % 60)).slice(-2);

        return currentdate.getFullYear() + "-" + ("0" + (currentdate.getMonth() + 1)).slice(-2) + "-" + ("0" + currentdate.getDate()).slice(-2) + "T" + ("0" + currentdate.getHours()).slice(-2) + ":"
            + ("0" + currentdate.getMinutes()).slice(-2) + ":"
            + ("0" + currentdate.getSeconds()).slice(-2) + timeZone;
    }

    learnNormal(detectorType) {
        this.anomalyDetector.learnNormal(detectorType);
    }

    createTrainTS(parsedJson) {
        this.anomalyDetector.createTrainTS(parsedJson);
    }

    createTestTS(parsedJson) {
        this.anomalyDetector.createTestTS(parsedJson);
    }

    detect() {
        this.anomalyDetector.detect();
    }

    getAnomalies() {
        return this.anomalyDetector.getAnomalies();
    }

    getJson() {
        return {model_id: this.model_id, upload_time: this.upload_time, status: this.status};
    }

    getFeatures() {
        return this.anomalyDetector.getFeatures();
    }

    updateStatus() {
        this.status = this.anomalyDetector.getStatus();
    }
}