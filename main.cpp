#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include "distance.h"
#include "tableVec.h"

#define KOMA ','

using namespace std;



template<typename T>

void printVector(vector<T>);

int numberOfValues(vector<tableVec>);

distanceType numberOfCalculation(string);

vector<string> turnLineIntoVector(string);

/*The main function that will
send the verctors to calculate.*/
int main() {
    vector<tableVec> fileVectors;
    fstream fin;
    string line, word, temp;
    vector<string> row;
    //open the file
    fin.open("datasets/iris/iris_classified.csv", ios_base::in);

    if (!fin.is_open()) {
        cout << "Open failed" << endl;
        return 1;
    }
    cout << "Open success" << endl;

    while (fin >> temp) {
        //initialize empty vector
        row.clear();
        //separate the values in temp into row
        row = turnLineIntoVector(temp);
        vector<double> doubles;
        for (int i = 0; i < row.size()-1; ++i) {
            doubles.push_back(stod(row.at(i)));
        }
        /**for testing */
        tableVec tempRow = tableVec(doubles, row.at(row.size()-1));
        printVector((tempRow.getVector()));
        fileVectors.push_back(tempRow);
        /**
        //initiate tableVec = temp
         * update the temp distance
         *vectors.add(temp);
         */

    }


    double input;
    vector<double> v1;
    try {
        int numValues, typeCalc;
        //Getting the number of values that a vector has in the table for valid checking
        numValues = numberOfValues(fileVectors);

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
    /**end of receiving the vector */


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
int numberOfValues(vector<tableVec> fileVectors) {
    int checkVecSize = fileVectors.at(0).getVector().size();
    int fileSize = fileVectors.size();
    for (int i = 1; i < fileSize; i++) {
        if(checkVecSize!= fileVectors.at(i).getVector().size())
        {
            throw invalid_argument("The file is invalid for not all the vectors are not in the same length");
        }

    }
    return checkVecSize;
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


vector<string> turnLineIntoVector(string line) {
    vector<string> row;
    string word;
    stringstream s(line);
    while (getline(s, word, KOMA)) {

        // add all the column data
        // of a row to a vector
        row.push_back(word);
    }
    return row;
}