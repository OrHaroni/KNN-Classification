#include <iostream>
#include <algorithm>
#include "Server.h"
#include "tableVec.h"
#include "FileVector.h"


using namespace std;

int mainValidation(int, string);

int main(int argc, char *argv[]) {
    int portNumber = 0;
    //Checking validation of the arguments.
    portNumber = mainValidation(argc, argv[2]);
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
    string answer;
    while (true) {
        try {
            try {
                answer = server.receive();
                cout << "This is what the server received: " << answer << endl;
            } catch (invalid_argument e) {
                //Not receiving so client disconnected
                //so listen to the next client
                server.listenServer();
                server.acceptServer();
                server.receive();
            }
            char* temp_answer = new char[answer.length() + 1];
            //getting the vector
            vector<double> vec = server.manipulateMSG(temp_answer);

            //getting the type
            distanceType distanceType = server.getDisType();
            //Checking if all the vectors have the same length
            //If not, the table is not valid so exit
            try {
                int sizeOfVectors = fileVectors.SizeOfVectors();
                if (vec.size() != sizeOfVectors) {
                    throw out_of_range("Invalid input");
                }
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

int mainValidation(int numArguments, string s_Port){
    int numPort = 0;
    //Validation of number of arguments
    if (numArguments != 3) {
        cout << "invalid number of arguments" << endl;
        throw invalid_argument("Got invalid number of arguments");
    }
    try {
        //Validation of the port
        numPort = stoi(s_Port);
    }
    catch (invalid_argument e) {
        cout << "invalid number of port" << endl;
        throw invalid_argument("invalid number of port");
    }
    //If we got here stoi worked and portNumber != 0
    if (numPort < 1024 || numPort > 65535) {
        cout << "invalid size of port" << endl;
        throw invalid_argument("invalid number of port");
    }
    return numPort;
}

