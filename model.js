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

        let datetime = currentdate.getFullYear() + "-" + ("0" + (currentdate.getMonth() + 1)).slice(-2) + "-" + ("0" + currentdate.getDate()).slice(-2) + "T" + ("0" + currentdate.getHours()).slice(-2) + ":"
            + ("0" + currentdate.getMinutes()).slice(-2) + ":"
            + ("0" + currentdate.getSeconds()).slice(-2) + timeZone;
        return datetime;
    }

    learnNormal(detectorType) {
        this.anomalyDetector.learnNormal(detectorType);
    }

    createTrainTS(path) {
        this.anomalyDetector.createTrainTS(path);
    }

    createTestTS(path) {
        this.anomalyDetector.createTestTS(path);
    }

    detect() {
        this.anomalyDetector.detect();
    }

    getAnomalies() {
        let startingIndexesMap = this.anomalyDetector.getAnomalies();
        let anomaliesArray = [];
        Object.entries(startingIndexesMap).forEach(entry => {
            const [key, value] = entry;
            anomaliesArray.push([parseInt(key), value]);
        });
        return anomaliesArray;
    }

    getJson() {
        return {model_id: this.model_id, upload_time: this.upload_time, status: this.status};
    }

    updateStatus(){
        this.status = this.anomalyDetector.getStatus();
    }

}