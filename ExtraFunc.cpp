#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include "tableVec.h"

#define COMMA ','

template<typename T>
void printVector(vector<T> v1) {
    for (int i = 0; i < v1.size(); i++) {
        cout << v1.at(i) << " ";
    }
    cout << endl;
}

//Checking the correct number of values of vector
static int numberOfValues(vector<tableVec> fileVectors) {
    int checkVecSize = fileVectors.at(0).getVector().size();
    int fileSize = fileVectors.size();

    for (int i = 1; i < fileSize - 1; i++) {
        //If we found empty vector, the file is invalid
        if (checkVecSize != fileVectors.at(i).getVector().size() && fileVectors.at(i).getVector().size() != 0) {

            throw invalid_argument("The file is invalid for not all the vectors are not in the same length");

        }
    }
    return checkVecSize;
}


//Returns the type of calculation with enum
static distanceType numberOfCalculation(string distance) {
    if (distance == "AUC") {
        return AUC;
    }
    if (distance == "MAN") {
        return MAN;
    }
    if (distance == "CHB") {
        return CHB;
    }
    if (distance == "CAN") {
        return CAN;
    }
    if (distance == "MIN") {
        return MIN;
    }
    //throws if the name of the type invalid
    throw invalid_argument("Invalid name of calculation.");

}

//Getting a line and return Vector that every value
//is a word\number of the line
static vector<string> turnLineIntoVector(string line) {
    vector<string> row;
    string word;
    stringstream s(line);
    //keep on separating the line with Comma's
    //until its empty
    while (getline(s, word, COMMA)) {
        if(s.eof()){
            break;
        }
        // add all the column data
        // of a row to a vector
        row.push_back(word);
    }
    //pushing the last one.
    row.push_back(word);
    return row;
}

//Compare for the sort of the vectors
static bool compareDistance(tableVec t1, tableVec t2) {
    return t1.getDistance() < t2.getDistance();
}

//Adding to the map. (Iterator template)
//If the type is not in the map, add it with 1 appearance.
//else, add 1 to the value (add 1 appearance)
static void addToMap(map<string, int>& neighbours, tableVec v1) {
    //first one with this type
    if (neighbours.find(v1.getType()) == neighbours.end()) {
        neighbours.insert({v1.getType(), 1});
    } else {
        neighbours.at(v1.getType())++;
    }
}


