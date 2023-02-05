#ifndef CLIONPROJECTS_SERVER_H
#define CLIONPROJECTS_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "tableVec.h"
#include "ExtraFunc.cpp"
#include <exception>
using namespace std;


class Server {
private:
    int m_server_port;
    struct sockaddr_in m_sin;
    int m_socket;
    struct sockaddr_in m_client_sin;
    int m_client_socket;
    char msg[4096];

public:
    Server(int);
    int getSocket();
    void bindServer();
    void listenServer();
    void acceptServer();
    void receive();
    void sendServer(char*);
    void closeServer();
    vector<double> manipulateMSG();
    distanceType getDisType() ;
    int getNumNeighbours();
};


#endif //CLIONPROJECTS_SERVER_H
