#ifndef CLIONPROJECTS_SERVER_H
#define CLIONPROJECTS_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "tableVec.h"
#include "ExtraFunc.cpp"
#include "ActiveClient.h"
#include <string.h>


using namespace std;
class ActiveClient;


class Server {
private:
    int m_server_port;
    struct sockaddr_in m_sin;
    int m_socket;
    struct sockaddr_in m_client_sin;
    int m_client_socket;
    char msg[4096];
    int lastIndexInMap;
    map<int, ActiveClient> clients;
    int currentThreadIndex;
    Command* commands[5];


public:
    Server(int);
    int getSocket() throw();
    void bindServer() throw();
    void listenServer() throw();
    void acceptServer(ActiveClient&) throw();
    string receive(ActiveClient&);
    void sendServer(string, ActiveClient&) throw();
    void closeServer() throw();
    vector<double> manipulateMSG(string) throw();
    distanceType getDisType(string) ;
    string getDisTypeString(distanceType);
    int getNumNeighbours() throw();
    void closeClient();
    void sendMenu(ActiveClient&);
};


#endif //CLIONPROJECTS_SERVER_H
