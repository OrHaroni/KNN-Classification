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
    int getSocket() throw();
    void bindServer() throw();
    void listenServer() throw();
    void acceptServer() throw();
    void receive();
    void sendServer(char*) throw();
    void closeServer() throw();
    vector<double> manipulateMSG() throw();
    distanceType getDisType() ;
    int getNumNeighbours() throw();
};


#endif //CLIONPROJECTS_SERVER_H
