//
// Created by or on 1/10/23.
//
#include "ActiveClient.h"
/*C'tor*/
ActiveClient::ActiveClient(FileVector* classified, FileVector* unClassified, int serverPorts, int indexInServerMap) : serverPort(serverPorts), indexInServerMap(indexInServerMap) {
    this->choiceNum = -1; //Initialize with invalid.
    this->k = 5; //Initialize with the value from the instructions.
    this->typeOfCalc = AUC; //Initialize with the value from the instructions.
    this->setClassifiedPath(classified);
    this->setUnClassifiedPath(unClassified);
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
FileVector* ActiveClient::getClassified(){
    return this->classified;
}
FileVector* ActiveClient::getUnClassified(){
    return this->unclassified;
}
int ActiveClient::getClientSocket() {
    return this->socket;
}
struct sockaddr_in ActiveClient::getSockStruct() {
    return this->sockStruct;
}

distanceType ActiveClient::getDisType() {
    return this->typeOfCalc;
}


/*Setters */
void ActiveClient::setChoiceNumber(int num) {
    this->choiceNum = num;
}
void ActiveClient::setKNumber(int newK) {
    this->k = newK;
}
void ActiveClient::setClassifiedPath(FileVector* path) {
    this->classified = path;
}
void ActiveClient::setUnClassifiedPath(FileVector* path) {
    this->unclassified = path;
}
void ActiveClient::setClientSocket(int sock) {
    this->socket = sock;
}
void ActiveClient::setSockStruct(sockaddr_in structSock) {
    this->sockStruct = structSock;
}

void ActiveClient::setDisType(distanceType type) {
    this->typeOfCalc = type;
}