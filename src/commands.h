//// Author: Aviad Saadi, ID: 212330567
//
//#ifndef COMMANDS_H_
//#define COMMANDS_H_
//
//#include<iostream>
//#include <string.h>
//
//#include <fstream>
//#include <vector>
//#include <sstream>
//#include <iosfwd>
//
//
//#include <sys/socket.h>
//#include <netinet/in.h>
//
//#include "pthread.h"
//#include <thread>
//
//#include <unistd.h>
//#include <iomanip>
//
//
//#include "HybridAnomalyDetector.h"
//
//using namespace std;
//
//class DefaultIO {
//public:
//    virtual string read() = 0;
//
//    virtual void write(string text) = 0;
//
//    virtual void write(float f) = 0;
//
//    virtual void read(float *f) = 0;
//
//    virtual ~DefaultIO() {}
//
//    // you may add additional methods here
//};
//
//class SocketIO : public DefaultIO {
//    int clientID;
//public:
//    SocketIO(int clientID) : clientID(clientID) {}
//
//    // read chars until until reading a new line char
//    string read() {
//        string msg = "";
//        char buff[1];
//
//        recv(this->clientID, buff, sizeof(char), 0);
//        while (buff[0] != 10) { //10 = "\n"
//            msg += buff[0];
//            bzero(buff, sizeof(char));
//            recv(this->clientID, buff, sizeof(char), 0);
//        }
//        return msg;
//
//    }
//    // write message to the current client
//    void write(string text) {
//        send(this->clientID, text.c_str(), text.length(), 0);
//    }
//
//    // write given float to the current client
//    void write(float f) {
//        std::string fStr = std::to_string(f);
//        fStr.erase(1 + fStr.find_last_not_of("0"), string::npos); // remove trailing zeros
//        send(this->clientID, fStr.c_str(), fStr.length(), 0);
//    }
//
//    // read number and put in into the given float
//    void read(float *f) {
//        string msg = "";
//        char buff[1];
//
//        recv(this->clientID, buff, sizeof(char), 0);
//        while (buff[0] != 10) { //10 = "\n"
//            msg += buff[0];
//            bzero(buff, sizeof(char));
//            recv(this->clientID, buff, sizeof(char), 0);
//        }
//        *f = stof(msg);
//    }
//
//    ~SocketIO() {}
//
//};
//
//// you may add here helper classes
//class AnomalySharedData {
//    HybridAnomalyDetector ad;
//    TimeSeries tsTest;
//    TimeSeries tsTrain;
//    vector<AnomalyReport> reportsVector;
//public:
//    AnomalySharedData() {
//
//    }
//
//    void initialize() { // initialize data - called after the files had been uploaded
//        this->ad = HybridAnomalyDetector();
//        this->tsTest = TimeSeries("anomalyTest.csv");
//        this->tsTrain = TimeSeries("anomalyTrain.csv");
//        this->reportsVector.clear();
//    }
//
//    float getThreshold() {
//        return this->ad.getThreshold();
//    }
//
//    void setThreshold(float threshold) {
//        this->ad.setThreshold(threshold);
//    }
//
//    void detectAnomalies() {
//        this->ad.learnNormal(this->tsTrain);
//        this->reportsVector = this->ad.detect(this->tsTest);
//    }
//
//    const vector<AnomalyReport> &getReportsVector() const {
//        return reportsVector;
//    }
//
//    int lengthOfTimeSeries() {
//        return this->tsTest.getNumOfRows();
//    }
//
//};
//
//// you may edit this class
//class Command {
//protected:
//    DefaultIO *dio;
//    string description;
//public:
//    Command(DefaultIO *dio, string description) : dio(dio), description(description) {}
//
//    string getDescription() {
//        return this->description;
//    }
//
//    virtual void execute() = 0;
//
//    virtual ~Command() {}
//};
//
//
//// implement here your command classes
//class MacroCommand : public Command {
//    vector<Command *> commands;
//
//
//public:
//    MacroCommand(DefaultIO *dio, string description) : Command(dio, description) {}
//
//    void execute() override {
//        for (auto command: commands) {
//            command->execute();
//        }
//    }
//
//    void addCommand(Command *command) {
//        this->commands.push_back(command);
//    }
//
//    virtual ~MacroCommand() {
//        for (auto command: commands) {
//            delete command;
//        }
//    }
//};
//
//class UploadCommand : public Command {
//    const char *fileName; //full name of file
//    string fileNameStr;
//public:
//    UploadCommand(DefaultIO *dio, string description, const char *fileName) : Command(dio, description),
//                                                                              fileName(fileName) {
//        this->fileNameStr = fileName;
//    }
//
//    // upload a file with a given name
//    void execute() override {
//        ofstream file(fileName);
//        if (file.is_open()) {
//            if (this->fileNameStr.compare("anomalyTest.csv") == 0) {
//                this->dio->write("Please upload your local test CSV file.\n");
//            } else if (this->fileNameStr.compare("anomalyTrain.csv") == 0) {
//                this->dio->write("Please upload your local train CSV file.\n");
//            } else if (this->fileNameStr.compare("localAnomalies.txt") == 0) {
//                this->dio->write("Please upload your local anomalies file.\n");
//            }
//            string line = this->dio->read();
//            while (line.compare("done") != 0) {
//                file << line + "\n";
//                line = this->dio->read();
//            }
//            file.close();
//            this->dio->write("Upload complete.\n");
//        }
//    }
//};
//
//
//class AnomalyDetectionCommand : public Command {
//protected:
//    AnomalySharedData *sharedData;
//public:
//    AnomalyDetectionCommand(DefaultIO *dio, string description, AnomalySharedData *sharedData) : Command(dio,
//                                                                                                         description),
//                                                                                                 sharedData(
//                                                                                                         sharedData) {}
//
//    virtual void execute() = 0;
//
//};
//
//class AlgorithmSettingsCommand : public AnomalyDetectionCommand {
//    void writeMessage(float threshold) {
//        this->dio->write("The current correlation threshold is ");
//        this->dio->write(threshold);
//        this->dio->write("\n");
//        this->dio->write("Type a new threshold\n");
//    }
//
//public:
//    AlgorithmSettingsCommand(DefaultIO *dio, string description, AnomalySharedData *sharedData)
//            : AnomalyDetectionCommand(dio,
//                                      description,
//                                      sharedData) {}
//
//    void execute() override {
//        float threshold = this->sharedData->getThreshold();
//        this->writeMessage(threshold);
//        this->dio->read(&threshold);
//
//        while (!(threshold >= 0 && threshold <= 1)) {
//            this->dio->write("please choose a value between 0 and 1.\n");
//            this->writeMessage(threshold);
//            this->dio->read(&threshold);
//        }
//        this->sharedData->setThreshold(threshold);
//    }
//};
//
//
//class DetectAnomaliesCommand : public AnomalyDetectionCommand {
//public:
//    DetectAnomaliesCommand(DefaultIO *dio, string description, AnomalySharedData *sharedData)
//            : AnomalyDetectionCommand(dio,
//                                      description,
//                                      sharedData) {}
//
//    void execute() override {
//        this->sharedData->detectAnomalies();
//        this->dio->write("anomaly detection complete.\n");
//    }
//};
//
//
//class DisplayResultsCommand : public AnomalyDetectionCommand {
//public:
//    DisplayResultsCommand(DefaultIO *dio, string description, AnomalySharedData *sharedData)
//            : AnomalyDetectionCommand(dio,
//                                      description,
//                                      sharedData) {}
//
//    void execute() override {
//        for (auto& report: this->sharedData->getReportsVector()) {
//            this->dio->write(report.timeStep);
//            this->dio->write("\t" + report.description + "\n");
//        }
//        this->dio->write("Done.\n");
//    }
//};
//
//class AnalyzeResults : public AnomalyDetectionCommand {
//    vector<pair<int, int>> givenStartAndFinishIndexes;
//    vector<pair<int, int>> continuousAnomaliesStartAndFinishIndexes;
//
//    void parseAnomaliesFile() {
//        bool isStart = true;
//        string line;
//        int val, startingIndex, endingIndex;
//        ifstream file("localAnomalies.txt");
//
//        if (!file.is_open()) throw runtime_error("Couldn't open file");
//        if (file.good()) { //if the file is ready to be read
//            while (getline(file, line)) { //for every line in the file (excluding the first one)
//                stringstream sstream(line);
//                isStart = true;
//                while (sstream >> val) { // if we havn't read all the line data
//                    if (isStart) {
//                        startingIndex = val;
//                        isStart = false;
//                    } else {
//                        endingIndex = val;
//                        pair<int, int> p(startingIndex, endingIndex);
//                        this->givenStartAndFinishIndexes.push_back(p);
//                    }
//                    if (sstream.peek() == ',') sstream.ignore(); // ignore commas
//                }
//            }
//            file.close(); //close the file
//        }
//
//    }
//
//    // unite sequence of anomalies with the same description
//    void uniteContinuousAnomalies() {
//        vector<AnomalyReport> reportsVector = this->sharedData->getReportsVector();
//        string description;
//        long timeStep;
//        int startingIndex, endingIndex;
//        for (int i = 0; i < reportsVector.size(); i++) {
//            description = reportsVector[i].description;
//            timeStep = reportsVector[i].timeStep;
//            startingIndex = timeStep;
//            endingIndex = startingIndex;
//            i++;
//            while (reportsVector[i].timeStep == timeStep + 1 &&
//                   reportsVector[i].description.compare(description) == 0) {
//                timeStep++;
//                endingIndex++;
//                i++;
//            }
//            pair<int, int> indexes(startingIndex, endingIndex);
//            this->continuousAnomaliesStartAndFinishIndexes.push_back(indexes);
//            i--;
//        }
//    }
//
//public:
//    AnalyzeResults(DefaultIO *dio, string description, AnomalySharedData *sharedData)
//            : AnomalyDetectionCommand(dio,
//                                      description,
//                                      sharedData) {}
//
//    void execute() override {
//        this->parseAnomaliesFile();
//        this->uniteContinuousAnomalies();
//        int P = this->givenStartAndFinishIndexes.size(); // number of given anomalies
//        //time steps without anomaly (from the anomaly file, not the algorithm)
//        int N = this->sharedData->lengthOfTimeSeries();
//        int falsePositiveCounter = 0, truePositiveCounter = 0;
//        bool isIntersects = false;
//
//        // calculate N
//        for (auto& indexesPair:this->givenStartAndFinishIndexes) {
//            N -= indexesPair.second - indexesPair.first + 1;
//        }
//
//        // calculate number of false positives
//        for (auto& algorithmIndexesPair:this->continuousAnomaliesStartAndFinishIndexes) {
//            isIntersects = false;
//            for (auto& givenIndexesPair:this->givenStartAndFinishIndexes) {
//                if (algorithmIndexesPair.second >= givenIndexesPair.first &&
//                    algorithmIndexesPair.first <= givenIndexesPair.second) {
//                    isIntersects = true;
//                    break;
//                }
//            }
//            if (!isIntersects) {
//                falsePositiveCounter++;
//            }
//        }
//
//        // calculate number of true positives
//        for (auto& givenIndexesPair:this->givenStartAndFinishIndexes) {
//            for (auto& algorithmIndexesPair:this->continuousAnomaliesStartAndFinishIndexes) {
//                if (givenIndexesPair.second >= algorithmIndexesPair.first &&
//                    givenIndexesPair.first <= algorithmIndexesPair.second) {
//                    truePositiveCounter++;
//                    break;
//                }
//            }
//        }
//
//        // calculte truePositiveRate, falseAlarmRate and floor them to have only three digit precision after the point
//        float truePositiveRate = (float) truePositiveCounter / P, falseAlarmRate = (float) falsePositiveCounter / N;
//        int tempTPR = truePositiveRate * 1000, tempFAR = 1000 * falseAlarmRate;
//        truePositiveRate = (float) tempTPR / 1000;
//        falseAlarmRate = (float) tempFAR / 1000;
//
//        this->dio->write("True Positive Rate: ");
//        this->dio->write(truePositiveRate);
//        this->dio->write("\n");
//
//        this->dio->write("False Positive Rate: ");
//        this->dio->write(falseAlarmRate);
//        this->dio->write("\n");
//
//        //empty vectors
//        this->givenStartAndFinishIndexes.clear();
//        this->continuousAnomaliesStartAndFinishIndexes.clear();
//    }
//
//};
//
//
//class ExitCommand : public Command {
//public:
//    ExitCommand(DefaultIO *dio, string description) : Command(dio, description) {}
//
//    void execute() {}
//};
//
//
//#endif /* COMMANDS_H_ */
