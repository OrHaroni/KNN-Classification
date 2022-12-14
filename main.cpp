#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include "tableVec.h"

#define COMMA ','

using namespace std;


template<typename T>

void printVector(vector<T>);

int numberOfValues(vector<tableVec>);

distanceType numberOfCalculation(string);

vector<string> turnLineIntoVector(string);

bool compareDistance(tableVec, tableVec);

void addToMap(map<string, int>, tableVec);

/*The main function that will
send the verctors to calculate.*/
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "invalid number of arguments (not 4 as expected)" << endl;
        return 1;
    }
    while (true) {
        vector<tableVec> fileVectors;
        fstream fin;
        string line, word, temp;
        vector<string> row;
        //open the file
        fin.open(argv[2], ios_base::in);

        if (!fin.is_open()) {
            cout << "The program failed to open the file (invalid path)" << endl;
            return 1;
        }

        while (fin >> temp) {
            //initialize empty vector
            row.clear();
            //separate the values in temp into row
            row = turnLineIntoVector(temp);
            vector<double> doubles;
            for (int i = 0; i < row.size() - 1; ++i) {
                doubles.push_back(stod(row.at(i)));
            }

            tableVec tempRow = tableVec(doubles, row.at(row.size() - 1));
            fileVectors.push_back(tempRow);
        }

        //getting the vector from the user
        double input;
        vector<double> v1;
        int numValues;
        distanceType typeCalc;
        try {

            //Getting the number of values that a vector has in the table for valid checking
            numValues = numberOfValues(fileVectors);

            //Getting the type of calc
            typeCalc = numberOfCalculation(argv[3]);

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

        for (int i = 0; i < fileVectors.size(); ++i) {
            fileVectors.at(i).calcDis(v1, typeCalc);
        }
        //sorting the vector
        sort(fileVectors.begin(), fileVectors.end(), compareDistance);
        //printing the K closest, try because of the stoi and invalid inputs
        try {
            int k = stoi(argv[1]);
            if (k < 0) {
                throw invalid_argument("cant have negative number of neighbours");
            }
            //if K is greater than the number of vectors we have,
            //so, all of the vectors are his neighbours, and we
            //need to print them.
            if (k > fileVectors.size()) {
                k = fileVectors.size();
            }
            map<string, int> neighbours;
            for (int i = 0; i < k; ++i) {
                cout << fileVectors.at(i).getDistance() << endl;
                addToMap(neighbours, fileVectors.at(i));
            }
            int maxType = 0;
            string maxTypeName = fileVectors.at(0).getType();
            for (int i = 0; i < neighbours.size(); ++i) {
                if (maxType < neighbours.at(fileVectors.at(i).getType())) {
                    maxType = neighbours.at(fileVectors.at(i).getType());
                    maxTypeName = fileVectors.at(i).getType();
                }
            }
            cout << "The type is:" << maxTypeName << endl;
        } //catches if argv[1] is not integer.
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return (1);
        }
    }
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
        if (checkVecSize != fileVectors.at(i).getVector().size()) {
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
    while (getline(s, word, COMMA)) {

        // add all the column data
        // of a row to a vector
        row.push_back(word);
    }
    return row;
}

bool compareDistance(tableVec t1, tableVec t2) {
    return t1.getDistance() < t2.getDistance();
}


void addToMap(map<string, int> neighbours, tableVec v1) {
    //first one with this type
    if (neighbours.find(v1.getType()) == neighbours.end()) {
        neighbours.insert({v1.getType(), 0});
    } else {
        neighbours.at(v1.getType())++;
    }
}

