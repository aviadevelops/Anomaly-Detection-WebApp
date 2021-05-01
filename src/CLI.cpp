//// Author: Aviad Saadi, ID: 212330567
//#include "CLI.h"
//
//CLI::CLI(DefaultIO *dio) : dio(dio) {
//     // initialize menu
//    auto *uploadTrain = new UploadCommand(dio, "", "anomalyTrain.csv");
//    auto *uploadTest = new UploadCommand(dio, "", "anomalyTest.csv");
//    auto *uploadFiles = new MacroCommand(dio, "1.upload a time series csv file\n");
//    uploadFiles->addCommand(uploadTrain);
//    uploadFiles->addCommand(uploadTest);
//    this->menuCommands.push_back(uploadFiles);
//    auto *changeAlgorithmSettings = new AlgorithmSettingsCommand(dio, "2.algorithm settings\n", &(this->sharedData));
//    this->menuCommands.push_back(changeAlgorithmSettings);
//    auto *detectAnomalies = new DetectAnomaliesCommand(dio, "3.detect anomalies\n", &(this->sharedData));
//    this->menuCommands.push_back(detectAnomalies);
//    auto *displayResults = new DisplayResultsCommand(dio, "4.display results\n", &(this->sharedData));
//    this->menuCommands.push_back(displayResults);
//    auto *uploadAnomalies = new UploadCommand(dio, "", "localAnomalies.txt");
//    auto *analyzeResults = new AnalyzeResults(dio, "", &(this->sharedData));
//    auto *uploadAnomaliesAndAnalyzeResults = new MacroCommand(dio, "5.upload anomalies and analyze results\n");
//    uploadAnomaliesAndAnalyzeResults->addCommand(uploadAnomalies);
//    uploadAnomaliesAndAnalyzeResults->addCommand(analyzeResults);
//    this->menuCommands.push_back(uploadAnomaliesAndAnalyzeResults);
//    auto *exitCommand = new ExitCommand(dio, "6.exit\n");
//    this->menuCommands.push_back(exitCommand);
//
//
//}
//
//// write menu options
//void CLI::writeMenu() {
//    this->dio->write("Welcome to the Anomaly Detection Server.\n");
//    this->dio->write("Please choose an option:\n");
//    for (auto command:this->menuCommands) {
//        this->dio->write(command->getDescription());
//    }
//}
//
//
//void CLI::start() {
//    this->writeMenu();
//    float userInput;
//    this->dio->read(&userInput);
//    int userOption = userInput;
//    while (true) {
//        if (userOption == 6) { //if the user wants to exit
//            break;
//        }
//        if (userOption >= 1 && userOption <= this->menuCommands.size()+1) {
//            this->menuCommands[userOption - 1]->execute();
//        }
//        if (userOption == 1) { // if we have uploaded new files
//            this->sharedData.initialize();
//        }
//        this->writeMenu();
//        this->dio->read(&userInput);
//        userOption = userInput;
//    }
//
//
//}
//
//
//CLI::~CLI() {
//    for (auto command:this->menuCommands) {
//        delete command;
//    }
//}
//
