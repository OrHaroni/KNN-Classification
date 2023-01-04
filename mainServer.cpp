#include <iostream>
#include <algorithm>
#include "Server.h"
#include "tableVec.h"


using namespace std;

int main(int argc, char *argv[]) {
    //Validation of number of arguments
    if(argc != 3){
        cout << "invalid number of arguments" << endl;
        return 1;
    }
    int portNumber = 0;
    try{
    //Validation of the port
    portNumber = stoi(argv[2]);
    }
    catch(invalid_argument e)
    {
        cout << "invalid number of port" << endl;
        return 1;
    }
    //If we got here stoi worked and portNumber != 0
    if(portNumber < 1024 || portNumber > 65535){
        cout << "invalid size of port" << endl;
        return 1;
    }
    //Creating a vector of table vectors for future compares.
    vector<tableVec> fileVectors;
    fstream fin;
    string line, word, temp;
    vector<string> row;
    Server server = Server(portNumber);
    //open the file
    fin.open(argv[1], ios_base::in);
    //Exiting if the file cant open.
    if (!fin.is_open()) {
        cout << "The program failed to open the file (invalid path)" << endl;
        return 1;
    }
    //Reading the file.
    try {
        while (getline(fin, temp)) {
            //initialize empty vector
            row.clear();
            //separate the values in temp into row
            row = turnLineIntoVector(temp);
            vector<double> doubles;
            for (int i = 0; i < row.size() - 1; ++i) {
                doubles.push_back(stod(row.at(i)));
            }

            //Adding temp vector from row to fileVectors
            string typeOfVec;
            tableVec tempRow = tableVec(doubles, row.at(row.size() - 1));
            fileVectors.push_back(tempRow);
        }
        server.bindServer();
        server.listenServer();
        server.acceptServer();
    } catch (invalid_argument e) {
        string invalid = "Invalid input";
        const int len = invalid.length();
        char *temp = new char[len + 1];
        strcpy(temp, invalid.c_str());
        server.sendServer(temp);
    }
    while (true) {
        try {
            try {
                server.receive();
            } catch (invalid_argument e){
                //Not receiving so client disconnected
                //so listen to the next client
                server.listenServer();
                server.acceptServer();
                server.receive();
            }
            //getting the vector
            vector<double> vec = server.manipulateMSG();

            //getting the type
            distanceType distanceType = server.getDisType();
            //Checking if all the vectors have the same length
            //If not, the table is not valid so exit
            try {
                int sizeOfVectors = numberOfValues(fileVectors);
                if(vec.size() != sizeOfVectors){
                    throw out_of_range("Invalid input");
                }
            }catch (invalid_argument e){
                cout << "not all the vectors in the file are in the same length so exiting" << endl;
                return 1;
            } catch(out_of_range e){
                throw invalid_argument("invalid input");
            }


            //getting the number of neighbours
            int k = server.getNumNeighbours();

            //Calculating all the distances from v1 for all the vectors in fileVectors
            for (int i = 0; i < fileVectors.size(); ++i) {
                fileVectors.at(i).calcDis(vec, distanceType);
            }

            //sorting the vector
            sort(fileVectors.begin(), fileVectors.end(), compareDistance);


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
            const int len = maxTypeName.length();
            char *temp = new char[len + 1];
            strcpy(temp, maxTypeName.c_str());
            server.sendServer(temp);

            //catches if getting invalid input.
        } catch (invalid_argument e) {
            string invalid = "Invalid input";
            const int len = invalid.length();
            char *temp = new char[len + 1];
            strcpy(temp, invalid.c_str());
            server.sendServer(temp);
        } catch (out_of_range e1) {
            string invalid = "Invalid input";
            const int len = invalid.length();
            char *temp = new char[len + 1];
            strcpy(temp, invalid.c_str());
            server.sendServer(temp);
        }
        catch(logic_error e) {
            string invalid = "Invalid input";
            const int len = invalid.length();
            char *temp = new char[len + 1];
            strcpy(temp, invalid.c_str());
            try {
                server.sendServer(temp);
            }
            catch(invalid_argument e){
                server.listenServer();
                server.acceptServer();
            }
        }
    }
}

