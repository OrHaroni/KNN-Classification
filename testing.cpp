//
// Created by or on 12/13/22.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>


using namespace std;
template <typename T>
void printVector(vector<T> v1)
{
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1.at(i) << " ";
    }
    cout << endl;
}

int main() {
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

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        cout << row[0] << endl;
        printVector(row);
    }
    else {
        cout << "Open failed" << endl;
        return 1;
    }

    return 0;
}