#include <iostream>
#include <algorithm>
#include "Server.h"
#include "tableVec.h"
#include "FileVector.h"


using namespace std;

int mainValidation(int, string);

int main(int argc, char *argv[]) {
    first_command c1 = first_command();
    second_command c2 = second_command();
    third_command c3 = third_command();
    fourth_command c4 = fourth_command();
    fifth_command c5 = fifth_command();
    Command *commands[5] = {&c1, &c2, &c3, &c4, &c5};
    int portNumber = 0;
    //Checking validation of the arguments.
    portNumber = mainValidation(argc, argv[2]);
    //Creating a vector of table vectors for future compares.
    FileVector classified_db = FileVector();
    FileVector unclassified_db = FileVector();
    Server server = Server(portNumber);
    try {
        classified_db.InitializeByReadingFile(argv[1]);
        server.bindServer();
        server.listenServer();
        server.acceptServer();
        server.sendMenu();
    } catch (invalid_argument e) {
        server.sendServer("Invalid input");
    }
    string choice;
    while (true) {
        try {
            choice = server.receive(); //Getting the number of choice from menu from the user.
        } catch (invalid_argument e) {
            //Not receiving so client disconnected
            //so listen to the next client
            server.listenServer();
            server.acceptServer();
            server.receive();
        }
        int choice_number = stoi(choice);
        if (choice_number == 3) {
            commands[2]->Execute(server, classified_db, unclassified_db);

        }else if(0 < choice_number && choice_number < 6){
            commands[choice_number - 1]->Execute(server, classified_db, unclassified_db);
            commands[choice_number - 1]->Execute(server, unclassified_db, classified_db);
            if(choice_number == 1){
                server.sendServer("Upload complete.");
            }
        }
        else {
            server.sendServer("Invalid choice");
        }
        server.sendMenu();
    }
}

int mainValidation(int numArguments, string s_Port) {
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

