//
// Created by Arthur on 5/1/2021.
//
#include <vector>
#include <map>
#include <napi.h>
#include "SimpleAsyncWorker.h"
#include <chrono>
#include <thread>
#include "helloworld.h"
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include "AnomalyDetector.h"
#include "SimpleAsyncWorker.h"

vector <AnomalyReport> reportsVector;
TimeSeries trainTS = TimeSeries(), testTS = TimeSeries();
SimpleAnomalyDetector simpleAD;
HybridAnomalyDetector hybridAD;
std::string status = "ready";
std::string detectorType;





SimpleAsyncWorker::SimpleAsyncWorker(Function& callback, int runTime)
    : AsyncWorker(callback), runTime(runTime){};

void SimpleAsyncWorker::Execute() {

};

void SimpleAsyncWorker::OnOK() {

};

void runSimpleAsyncWorker(const CallbackInfo& info) {
  int runTime = info[0].As<Number>();
  Function callback = info[1].As<Function>();
  SimpleAsyncWorker* asyncWorker = new SimpleAsyncWorker(callback, runTime);
  asyncWorker->Queue();
};

// unite sequence of anomalies with the same description
// unite sequence of anomalies with the same description
std::map<std::string, std::vector<std::pair<int, int>>> uniteContinuousAnomalies() {
    std::map<std::string, std::vector<std::pair<int, int>>> continuousAnomaliesStartAndFinishIndexes;
    std::string description;
    long timeStep;
    int startingIndex, endingIndex;
    for (int i = 0; i < reportsVector.size(); i++) {
        description = reportsVector[i].description;
        timeStep = reportsVector[i].timeStep;
        startingIndex = timeStep;
        endingIndex = startingIndex;
        i++;
        while (reportsVector[i].timeStep == timeStep + 1 &&
               reportsVector[i].description.compare(description) == 0) {
            timeStep++;
            endingIndex++;
            i++;
        }
        std::string columnName = description.substr(0, description.find("-"));
        std::pair<int, int> indexes(startingIndex, endingIndex);
        continuousAnomaliesStartAndFinishIndexes[columnName].push_back(indexes);
        i--;
    }
    return continuousAnomaliesStartAndFinishIndexes;
}


map <std::string, std::string> objectToMap(Napi::Object object) {

    map <std::string, std::string> newMap;
    auto keys = object.GetPropertyNames();
    const auto N = keys.Length();
    Napi::Value val;
    std::string key;
    std::string value;
    for (auto i = 0; i < N; i++) {
        val = keys[i];
        key = val.ToString();
        value = object.Get(keys[i]).ToString();
        newMap.insert({key, value});
    }
    return newMap;
}

void createTrainTS(const Napi::CallbackInfo &info) {

    Napi::Env env = info.Env();
    map <std::string, std::string> newMap = objectToMap(info[0].As<Napi::Object>());
    trainTS = TimeSeries(newMap);
}


void createTestTS(const Napi::CallbackInfo &info) {

    Napi::Env env = info.Env();
    map <std::string, std::string> newMap = objectToMap(info[0].As<Napi::Object>());
    testTS = TimeSeries(newMap);
}

void learnNormal(const Napi::CallbackInfo &info) {

    status = "pending";

    Napi::Env env = info.Env();
    detectorType = info[0].As<Napi::String>();
    if (detectorType == "hybrid") {
        hybridAD.learnNormal(trainTS);
    } else {
        simpleAD.learnNormal(trainTS);
    }

    status = "ready";
}

void detect(const Napi::CallbackInfo &info) {

    status = "pending";

    Napi::Env env = info.Env();
    if (detectorType == "hybrid") {
        reportsVector = hybridAD.detect(testTS);
    } else {
        reportsVector = simpleAD.detect(testTS);
    }

    status = "ready";


}

Napi::Object getAnomalies(const Napi::CallbackInfo &info) {

    Napi::Env env = info.Env();

    std::map<std::string, std::vector<std::pair<int, int>>> anomalies = uniteContinuousAnomalies();
    Napi::Object startingIndexesMap = Napi::Object::New(env);
    for(auto p:anomalies)
    {
        Napi::Object anomalySpan = Napi::Object::New(env);
        for(auto pair: p.second){
            anomalySpan.Set(pair.first,pair.second);
        }
        startingIndexesMap.Set(p.first,anomalySpan);
    }
    return startingIndexesMap;
}

Napi::String getStatus(const Napi::CallbackInfo &info) {

    Napi::Env env = info.Env();

    return Napi::String::New(env, status);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {


    exports.Set(Napi::String::New(env, "createTrainTS"),
                Napi::Function::New(env, createTrainTS)
    );

    exports.Set(Napi::String::New(env, "createTestTS"),
                Napi::Function::New(env, createTestTS)
    );

    exports.Set(Napi::String::New(env, "learnNormal"),
                Napi::Function::New(env, learnNormal)
    );

    exports.Set(Napi::String::New(env, "detect"),
                Napi::Function::New(env, detect)
    );

    exports.Set(Napi::String::New(env, "getAnomalies"),
                Napi::Function::New(env, getAnomalies)
    );

    exports.Set(Napi::String::New(env, "getStatus"),
                Napi::Function::New(env, getStatus)
    );

    exports["runSimpleAsyncWorker"] = Function::New(
          env, runSimpleAsyncWorker, std::string("runSimpleAsyncWorker"));

    return exports;
}

NODE_API_MODULE(anomalydetector, Init)

