#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include "tableVec.h"
#include "Server.h"
#include "Client.h"

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
  /**  if (argc != 4) {
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
        //Exiting if the file cant open.
        if (!fin.is_open()) {
            cout << "The program failed to open the file (invalid path)" << endl;
            return 1;
        }
        //Reading the file.
        while (getline(fin, temp)) {
            //initialize empty vector
            row.clear();
            //separate the values in temp into row
            row = turnLineIntoVector(temp);
            vector<double> doubles;
            for (int i = 0; i < row.size() - 1; ++i) {
                doubles.push_back(stod(row.at(i)));
            }
            string typeOfVec;
            tableVec tempRow = tableVec(doubles, row.at(row.size() -1));
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
        //Throws if get a letter in the input or too much values
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return (1);
        }

        //Calculating all the distances from v1 for all the vectors in fileVectors
        for (int i = 0; i < fileVectors.size(); ++i) {
            fileVectors.at(i).calcDis(v1, typeCalc);
        }
**/


        Server server = Server(123456);
        server.getSocket();
        server.bindServer();
        server.listenServer();

        Client client = Client("127.0.0.1", 123456);
        int client_socket = client.getNewSocket();
        if(client_socket < 0)
        {
            throw invalid_argument("client cant create socket");
        }
        client.setSocket(client_socket);
        client.startSin();
        if(client.clientConnect() < 0)
        {
            throw invalid_argument("client cant connect");
        }

        server.acceptServer();

        client.sendVector();

        server.receive();

        //Close the sockets
        server.closeServer();
        client.closeClient();


/**
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
            //Creating map that the key is the type
            //and the value is the times this type
            //appears in the file
            map<string, int> neighbours;
            for (int i = 0; i < k; ++i) {
                addToMap(neighbours, fileVectors.at(i));
            }

            //Checking the largest value of the map.
            //Its the repeated type.
            int maxType = 0;
            string maxTypeName = fileVectors.at(0).getType();
            for (int i = 0; i < neighbours.size(); ++i) {
                if (maxType < neighbours.at(fileVectors.at(i).getType())) {
                    maxType = neighbours.at(fileVectors.at(i).getType());
                    maxTypeName = fileVectors.at(i).getType();
                }
            }
            cout << maxTypeName << endl;
        } //catches if argv[1] is not integer.
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return (1);
        }
    }
    **/
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

    for (int i = 1; i < fileSize - 1; i++) {
        //If we found empty vector, the file is invalid
        if (checkVecSize != fileVectors.at(i).getVector().size() && fileVectors.at(i).getVector().size() != 0) {

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
    //throws if the name of the type invalid
    throw invalid_argument("Invalid name of calculation.");

}

//Getting a line and return Vector that every value
//is a word\number of the line
vector<string> turnLineIntoVector(string line) {
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
bool compareDistance(tableVec t1, tableVec t2) {
    return t1.getDistance() < t2.getDistance();
}

//Adding to the map. (Iterator template)
//If the type is not in the map, add it with 1 appearance.
//else, add 1 to the value (add 1 appearance)
void addToMap(map<string, int> neighbours, tableVec v1) {
    //first one with this type
    if (neighbours.find(v1.getType()) == neighbours.end()) {
        neighbours.insert({v1.getType(), 1});
    } else {
        neighbours.at(v1.getType())++;
    }
}

