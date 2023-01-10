#ifndef CLIONPROJECTS_ACTIVECLIENT_H
#define CLIONPROJECTS_ACTIVECLIENT_H


#include "tableVec.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

class ActiveClient {
private:

    int choiceNum = -1;
    int k = 5;
    distanceType typeOfCalc = AUC;
    char* classifiedPath = NULL;
    char* unclassifiedPath = NULL;
    int socket = 0;
    struct sockaddr_in sockStruct;
    int serverPort;
    int indexInServerMap;

public:
    //C'tor
    ActiveClient(int, int);

    //Getters
    int getChoiceNumber();
    int getKNumber();
    char* getClassifiedPath();
    char* getUnClassifiedPath();
    int getClientSocket();
    struct sockaddr_in getSockStruct();

    //Setters
    void setChoiceNumber(int);
    void setKNumber(int);
    void setClassifiedPath(char*);
    void setUnClassifiedPath(char*);
    void setClientSocket(int);
    void setSockStruct(sockaddr_in);


};


#endif //CLIONPROJECTS_ACTIVECLIENT_H
