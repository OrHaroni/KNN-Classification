#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include "distance.h"

using namespace std;
#define FOUR 4
template <typename T>

void printVector(vector<T>);
int numberOfValues(string);


/*The main function that will
send the verctors to calculate.*/
int main()
{
    int numValues;
    //Getting the number of values that a vector has in the table for valid checking
    numValues = numberOfValues("datasets/iris/iris_classified.csv");
    if(numValues < 0){
        throw invalid_argument("Could not open the file.");
    }
    double input;
    vector<double> v1;
        try {
            // getting v1
            do
            {
                if (std::cin >> input)
                {
                    v1.push_back(input);
                }
            } while (std::cin && std::cin.peek() != '\n');

            if (cin.peek() != '\n') {
                throw invalid_argument("Received invalid input.");
            }
            if (v1.size() != numValues) {
                throw invalid_argument("Invalid length of the vector.");
            }
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return (1);
        }

        printVector(v1);


    return 0;
}

// Func for testing
template <typename T>
void printVector(vector<T> v1)
{
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1.at(i) << " ";
    }
    cout << endl;
}

//Checking the correct number of values of vector
int numberOfValues(string path) {
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
    return -1;
}

int numberOfCalculation(string distance) {
    if(distance ==  "AUC"){
        return 1;
    }

}