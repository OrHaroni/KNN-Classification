//
// Created by or on 1/10/23.
//
#include "CLI.h"
/*C'tor*/
CLI::CLI(FileVector* classified, FileVector* unClassified, int serverPorts, int indexInServerMap) : serverPort(serverPorts), indexInServerMap(indexInServerMap), isClassified(false) {
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
int CLI::getChoiceNumber(){
    return this->choiceNum;
}
int CLI::getKNumber(){
    return this->k;
}
FileVector* CLI::getClassified(){
    return this->classified;
}
FileVector* CLI::getUnClassified(){
    return this->unclassified;
}
int CLI::getClientSocket() {
    return this->socket;
}
struct sockaddr_in CLI::getSockStruct() {
    return this->sockStruct;
}

distanceType CLI::getDisType() {
    return this->typeOfCalc;
}

/*Setters */
void CLI::setChoiceNumber(int num) {
    this->choiceNum = num;
}
void CLI::setKNumber(int newK) {
    this->k = newK;
}
void CLI::setClassifiedPath(FileVector* path) {
    this->classified = path;
}
void CLI::setUnClassifiedPath(FileVector* path) {
    this->unclassified = path;
}
void CLI::setClientSocket(int sock) {
    this->socket = sock;
}
void CLI::setSockStruct(sockaddr_in structSock) {
    this->sockStruct = structSock;
}

void CLI::setDisType(distanceType type) {
    this->typeOfCalc = type;
}

void CLI::classifyTheData() {
    this->isClassified = true;
    cout << " Now the data is classified" << endl;
}

bool CLI::isClassifiedTheData() {
    return this->isClassified;
}