#include <iostream>
#include <algorithm>
#include "Server.h"
#include "tableVec.h"
#include "FileVector.h"


using namespace std;

int main(int argc, char *argv[]) {
    //Validation of number of arguments
    if (argc != 3) {
        cout << "invalid number of arguments" << endl;
        return 1;
    }
    int portNumber = 0;
    try {
        //Validation of the port
        portNumber = stoi(argv[2]);
    }
    catch (invalid_argument e) {
        cout << "invalid number of port" << endl;
        return 1;
    }
    //If we got here stoi worked and portNumber != 0
    if (portNumber < 1024 || portNumber > 65535) {
        cout << "invalid size of port" << endl;
        return 1;
    }
    //Creating a vector of table vectors for future compares.
    FileVector fileVectors = FileVector();
    Server server = Server(portNumber);
    try {
        fileVectors.InitializeByReadingFile(argv[1]);
        server.bindServer();
        server.listenServer();
        server.acceptServer();
        server.sendMenu();
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
            } catch (invalid_argument e) {
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
                int sizeOfVectors = fileVectors.SizeOfVectors();
                cout << "this is vec.size: " << vec.size() << " And this is size: " << sizeOfVectors << endl;
                if (vec.size() != sizeOfVectors) {
                    throw out_of_range("Invalid input");
                }
                cout << "We got to line 95" << endl;
            } catch (invalid_argument e) {
                cout << "not all the vectors in the file are in the same length so exiting" << endl;
                return 1;
            } catch (out_of_range e) {
                throw invalid_argument("invalid input");
            }

            //getting the number of neighbours
            int k = server.getNumNeighbours();

            string s = fileVectors.CalcTypeName(k, vec, distanceType);
            char *temp = new char[s.length() + 1];
            ::strcpy(temp, s.c_str());
            cout << "this is temp, what we are sending" << temp << endl;
            server.sendServer(temp);

            //catches if getting invalid input.
        } catch (invalid_argument e) {
            cout << "This is what throwing us: " << e.what() << endl;
            string invalid = "Invalid input 1";
            const int len = invalid.length();
            char *temp = new char[len + 1];
            strcpy(temp, invalid.c_str());
            server.sendServer(temp);
        } catch (out_of_range e1) {
            string invalid = "Invalid input 2";
            const int len = invalid.length();
            char *temp = new char[len + 1];
            strcpy(temp, invalid.c_str());
            server.sendServer(temp);
        }
        catch (logic_error e) {
            string invalid = "Invalid input 3";
            const int len = invalid.length();
            char *temp = new char[len + 1];
            strcpy(temp, invalid.c_str());
            try {
                server.sendServer(temp);
            }
            catch (invalid_argument e) {
                server.listenServer();
                server.acceptServer();
            }
        }
    }
}

