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
    int getSocket() throw();
    void bindServer() throw();
    void listenServer() throw();
    void acceptServer(CLI&) throw();
    string receive(CLI&);
    void sendServer(string, CLI&) throw();
    void closeServer() throw();
    vector<double> manipulateMSGWIthType(string) throw();
    vector<double> manipulateMSGWithoutType(string) throw();
    distanceType getDisType(string) ;
    string getDisTypeString(distanceType);
    int getNumNeighbours() throw();
    int getPortNumber();
    void closeClient();
    void sendMenu(CLI&);
};


#endif //CLIONPROJECTS_SERVER_H
