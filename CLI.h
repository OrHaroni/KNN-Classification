#ifndef CLIONPROJECTS_CLI_H
#define CLIONPROJECTS_CLI_H


#include "tableVec.h"
#include "FileVector.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;
class Server;
class FileVector;

class CLI {
private:
    int choiceNum = -1;
    int k;
    distanceType typeOfCalc = AUC;
    FileVector* classified;
    FileVector* unclassified;
    int socket = 0;
    struct sockaddr_in sockStruct;
    int serverPort;
    int indexInServerMap;
    bool isClassified;

public:
    //C'tor
    CLI(FileVector*, FileVector*, int, int);

    //Getters
    int getChoiceNumber();
    int getKNumber();
    FileVector* getClassified();
    FileVector* getUnClassified();
    int getClientSocket();
    struct sockaddr_in getSockStruct();
    distanceType getDisType();

    //Setters
    void setChoiceNumber(int);
    void setKNumber(int);
    void setClassifiedPath(FileVector*);
    void setUnClassifiedPath(FileVector*);
    void setClientSocket(int);
    void setSockStruct(sockaddr_in);
    void setDisType(distanceType);
    void classifyTheData();
    bool isClassifiedTheData();
};


#endif //CLIONPROJECTS_CLI_H
