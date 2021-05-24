//// Author: Aviad Saadi, ID: 212330567
//
//#ifndef SERVER_H_
//#define SERVER_H_
//
//#include <iostream>
//#include <sys/socket.h>
//#include <netinet/in.h>
//
//#include "pthread.h"
//#include <thread>
//
//#include <unistd.h>
//#include <string.h>
//
//#include "commands.h"
//#include "CLI.h"
//
//
//using namespace std;
//
//// edit your ClientHandler interface here:
//class ClientHandler {
//public:
//    virtual void handle(int clientID) = 0;
//};
//
//
//// you can add helper classes here and implement on the cpp file
//
//
//// edit your AnomalyDetectionHandler class here
//class AnomalyDetectionHandler : public ClientHandler {
//
//public:
//    virtual void handle(int clientID) {
//        SocketIO socketIo(clientID); //create a new socketIO
//        CLI cli(&socketIo); //create a new cli with the socketIO
//        cli.start(); // start the CLI
//    }
//};
//
//
//// implement on Server.cpp
//class Server {
//    thread *startServerThread; // the thread to run the start() method in
//    // you may add data members
//    int fd, clientLimit; //file descriptors
//    sockaddr_in serverAddr, clientAddr;
//    volatile bool toStopServerLoop = false;
//
//public:
//    Server(int port) throw(const char *);
//
//    virtual ~Server();
//
//    void start(ClientHandler &ch) throw(const char *);
//
//    void handleNewClient(ClientHandler &ch, int clientID);
//
//    void stop();
//};
//
//#endif /* SERVER_H_ */
