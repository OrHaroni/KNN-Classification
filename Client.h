#ifndef ADVANCEDPROGPROJECT_CLIENT_H
#define ADVANCEDPROGPROJECT_CLIENT_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "tableVec.h"
using namespace std;

class Client {
private:
    const char* m_ip_address;
    int m_port_no;
    int m_socket;
    struct sockaddr_in m_sin;


public:
    Client(const char*, int);
    void getNewSocket() throw();
    void startSin();
    void clientConnect() throw();
    void sendVector(char*) throw();
    string receive() throw();
    void disconnect();

};


#endif //ADVANCEDPROGPROJECT_CLIENT_H