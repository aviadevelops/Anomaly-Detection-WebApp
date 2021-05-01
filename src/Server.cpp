//// Author: Aviad Saadi, ID: 212330567
//#include "Server.h"
//
// // initialize server - initialize socket, bind and listen
//Server::Server(int port) throw(const char *) {
//    this->fd = socket(AF_INET, SOCK_STREAM, 0);
//    if (this->fd < 0) {
//        throw "Socket Opening Failed.";
//    }
//    this->serverAddr.sin_family = AF_INET; // ipv4
//    this->serverAddr.sin_addr.s_addr = INADDR_ANY; // setting ip address to be local host
//    this->serverAddr.sin_port = htons(port);
//    if (bind(this->fd, (struct sockaddr *) &(this->serverAddr), sizeof(this->serverAddr)) < 0) {
//        throw "Binding Failed.";
//    }
//    this->clientLimit = 5;
//    if (listen(this->fd, this->clientLimit) < 0) {
//        throw "Listening Failed.";
//    }
//
//}
//
//// handle client communication and close its socket afterwards
//void Server::handleNewClient(ClientHandler &ch, int clientID) {
//    ch.handle(clientID);
//    close(clientID);
//}
//
//// starting sever - putting the accept in a loop to be able to communicate with multiple clients,
//// putting the accept in a thread so it won't be a blocking call
//void Server::start(ClientHandler &ch) throw(const char *) {
//    this->startServerThread = new thread([&ch, this]() {
//        while (!this->toStopServerLoop) {
//            socklen_t currentClientSize = sizeof(this->clientAddr);
//            alarm(1);
//            int currentClient = accept(this->fd, (struct sockaddr *) &(this->clientAddr), &currentClientSize);
//            alarm(0);
//            if (currentClient < 0) {
//                throw "Accepting Failed.";
//            }
//            handleNewClient(ch, currentClient);
//        }
//    });
//
//
//}
//
//void Server::stop() {
//    this->toStopServerLoop = true; // stop the loop
//    startServerThread->join(); // wait for the sever thread to finish his tasks
//    close(this->fd); // close the server socket
//}
//
//Server::~Server() {
//}
//
