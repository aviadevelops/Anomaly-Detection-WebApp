//
// Created by Arthur on 5/1/2021.
//
#include <napi.h>
#include "helloworld.h"
#include "timeseries.h"
#include <vector>
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include "AnomalyDetector.h"

vector<AnomalyReport> reportsVector;
TimeSeries trainTS = TimeSeries(), testTS = TimeSeries();
SimpleAnomalyDetector simpleAD;
HybridAnomalyDetector hybridAD;
bool isHybrid = true;


 // unite sequence of anomalies with the same description
    vector<pair<int, int>> uniteContinuousAnomalies() {
        vector<pair<int, int>> continuousAnomaliesStartAndFinishIndexes;
        string description;
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
            pair<int, int> indexes(startingIndex, endingIndex);
            continuousAnomaliesStartAndFinishIndexes.push_back(indexes);
            i--;
        }
       return continuousAnomaliesStartAndFinishIndexes;
    }

Napi::String getHello(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();

      double arg0 = info[0].As<Napi::Number>().DoubleValue();
      double arg1 = info[1].As<Napi::Number>().DoubleValue();
      double sum = arg0+arg1;

    std::string result = helloworld::hello()+std::to_string(sum);

    return Napi::String::New(env, result);
}

Napi::String getSig(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();

     std::string arg0 = info[0].As<Napi::String>();
     std::string arg1 = info[1].As<Napi::String>();

    std::string result = arg0+arg1;

    return Napi::String::New(env, result);
}



void createTrainTS(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();
    std::string trainPath = info[0].As<Napi::String>();
    trainTS = TimeSeries(trainPath);
}


void createTestTS(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();
    std::string testPath = info[0].As<Napi::String>();
    testTS = TimeSeries(testPath);
}

void learnNormal(const Napi::CallbackInfo& info){

    Napi::Env env = info.Env();
    if(isHybrid){
        hybridAD.learnNormal(trainTS);
    }
    else{
        simpleAD.learnNormal(trainTS);
    }

}

void detect(const Napi::CallbackInfo& info){

    Napi::Env env = info.Env();
    if(isHybrid){
        reportsVector = hybridAD.detect(testTS);
    }
    else{
        reportsVector = simpleAD.detect(testTS);
    }

}

Napi::Object getAnomalies(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();



    vector<pair<int, int>> anomalies = uniteContinuousAnomalies();
    std::string result="";
    Napi::Object startingIndexesMap = Napi::Object::New(env);
    int i=0;
    for(pair<int,int> p:anomalies)
    {
        startingIndexesMap.Set(p.first,p.second);
    }
    return startingIndexesMap;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {

    exports.Set(
        Napi::String::New(env, "getHello"),
        Napi::Function::New(env, getHello)
    );

    exports.Set(Napi::String::New(env, "getSig"),
                Napi::Function::New(env, getSig)
    );

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



    return exports;
}

NODE_API_MODULE(anomalydetector, Init)

