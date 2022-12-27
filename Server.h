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

using namespace std;
class Server {
private:
    int m_server_port;
    struct sockaddr_in m_sin;
    int m_socket;
    struct sockaddr_in m_client_sin;
    int m_client_socket;

public:
    Server(int, int);
    void getSocket() throw();
    void bind() throw();
    void listen() throw();
    void accept() throw();
    vector<double> receive() throw();
    void send() throw();
};


#endif //CLIONPROJECTS_SERVER_H
