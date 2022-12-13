#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <list>
#include "distance.h"
#include "tableVec.h"

#define KOMA ','

using namespace std;



template<typename T>

void printVector(vector<T>);

unsigned long  numberOfValues(string);

distanceType numberOfCalculation(string);

vector<string> turnLineIntoVector(string);

/*The main function that will
send the verctors to calculate.*/
int main() {
    list<tableVec> vectors;
    double input;
    vector<double> v1;
    try {
        int numValues, typeCalc;
        //Getting the number of values that a vector has in the table for valid checking
        numValues = numberOfValues("datasets/iris/iris_classified.csv");

        //Getting the type of calc
        typeCalc = numberOfCalculation("AUC");

        // getting v1
        do {
            if (std::cin >> input) {
                v1.push_back(input);
            }
        } while (std::cin && std::cin.peek() != '\n');

        //if the Buffer is not empty (peak not \n) there was invalid char.
        if (cin.peek() != '\n') {
            throw invalid_argument("Received invalid input.");
        }
        //if the size of the vector is not like the ones in the tables its invalid.
        if (v1.size() != numValues) {
            throw invalid_argument("Invalid length of the vector.");
        }
    }
    catch (invalid_argument e) {
        cout << e.what() << endl;
        return (1);
    }
    printVector(v1);
    
    fstream fin;
    //Opening the file from the path
    fin.open("datasets/iris/iris_classified.csv", ios_base::in);

    if (fin.is_open()){
        cout << "Open success" << endl;
        //Every value of the vector is a cell.
        vector<string> row;
        string line, word, temp;
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        row = turnLineIntoVector(line);
        printVector(row);

        /**
        //initiate tableVec = temp
         * update the temp distance
         *vectors.add(temp);
         */
    }
    else {
        cout << "Open failed" << endl;
        return 1;
    }



    return 0;
}

// Func for testing
template<typename T>
void printVector(vector<T> v1) {
    for (int i = 0; i < v1.size(); i++) {
        cout << v1.at(i) << " ";
    }
    cout << endl;
}

//Checking the correct number of values of vector
unsigned long numberOfValues(string path) {
    fstream fin;
    fin.open(path, ios_base::in);
    if (fin.is_open()) {
        //Every value of the vector is a cell.
        vector<string> row;
        string line, word, temp;
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        return row.size() - 1;
    }
    throw invalid_argument("Could not open the file.");
}


//Returns the type of calculation with enum
distanceType numberOfCalculation(string distance) {
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
    throw invalid_argument("Invalid name of calculation.");

}

//
vector<string> turnLineIntoVector(string line) {
    vector<string> row;
    string word;
    stringstream s(line);
    while(getline(s, word, KOMA)) {

        // add all the column data
        // of a row to a vector
        row.push_back(word);
    }
}