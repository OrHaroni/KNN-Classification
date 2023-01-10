//
// Created by or on 1/10/23.
//
#include "ActiveClient.h"
/*C'tor*/
ActiveClient::ActiveClient(int serverPorts, int indexInServerMap) : serverPort(serverPorts), indexInServerMap(indexInServerMap) {
    this->choiceNum = -1; //Initialize with invalid.
    this->k = 5; //Initialize with the value from the instructions.
    this->typeOfCalc = AUC; //Initialize with the value from the instructions.
    this->classifiedPath = nullptr; //Initialize with null so we know whether the client inserted a path or not
    this->unclassifiedPath = nullptr; //Initialize with null so we know whether the client inserted a path or not
    this->socket = 0;
    this->sockStruct.sin_family = AF_INET;
    this->sockStruct.sin_addr.s_addr = INADDR_ANY;
    this->sockStruct.sin_port = htons(serverPort);
    //Initializing the client's struct without values.
    memset(&this->sockStruct, 0, sizeof(this->sockStruct));//Initializing the struct
}


/*Getters */
int ActiveClient::getChoiceNumber(){
    return this->choiceNum;
}
int ActiveClient::getKNumber(){
    return this->k;
}
char* ActiveClient::getClassifiedPath(){
    return this->classifiedPath;
}
char* ActiveClient::getUnClassifiedPath(){
    return this->unclassifiedPath;
}
int ActiveClient::getClientSocket() {
    return this->socket;
}
struct sockaddr_in ActiveClient::getSockStruct() {
    return this->sockStruct;
}


/*Setters */
void ActiveClient::setChoiceNumber(int num) {
    this->choiceNum = num;
}
void ActiveClient::setKNumber(int newK) {
    this->k = newK;
}
void ActiveClient::setClassifiedPath(char* path) {
    this->classifiedPath = path;
}
void ActiveClient::setUnClassifiedPath(char* path) {
    this->unclassifiedPath = path;
}
void ActiveClient::setClientSocket(int sock) {
    this->socket = sock;
}
void ActiveClient::setSockStruct(sockaddr_in structSock) {
    this->sockStruct = structSock;
}
