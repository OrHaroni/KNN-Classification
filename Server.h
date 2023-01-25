#ifndef CLIONPROJECTS_SERVER_H
#define CLIONPROJECTS_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "tableVec.h"
#include "ExtraFunc.cpp"
#include "CLI.h"
#include <string.h>
#include <exception>

using namespace std;
class CLI;


class Server {
private:
    int m_server_port;
    struct sockaddr_in m_sin;
    int m_socket;
    struct sockaddr_in m_client_sin;
    int m_client_socket;
    char msg[4096];
    int lastIndexInMap;
    map<int, CLI> clients;
    int currentThreadIndex;
    Command* commands[5];


public:
    Server(int);
    int getSocket();
    void bindServer();
    void listenServer();
    void acceptServer(CLI&);
    string receive(CLI&);
    void sendServer(string, CLI&);
    void closeServer();
    vector<double> manipulateMSGWIthType(string);
    vector<double> manipulateMSGWithoutType(string);
    distanceType getDisType(string) ;
    string getDisTypeString(distanceType);
    int getNumNeighbours();
    int getPortNumber();
    void closeClient();
    void sendMenu(CLI&);
};


#endif //CLIONPROJECTS_SERVER_H
