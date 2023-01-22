#include <iostream>
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
    try {
        portNumber = mainValidation(argc, argv[1]);
    }catch (invalid_argument e){
        cout << e.what() << endl;
        return 1;
    }
    //Creating a vector of table vectors for future compares.
    FileVector classified_db = FileVector();
    FileVector unclassified_db = FileVector();
    ActiveClient client = ActiveClient(&classified_db, &unclassified_db, portNumber ,1);
    Server server = Server(portNumber);
    try {
        server.bindServer();
        server.listenServer();
        server.acceptServer(client);
        server.sendMenu(client);
    } catch (invalid_argument e) {
        server.sendServer("Invalid input", client);
    }
    string choice;
    while (true) {
        try {
            choice = server.receive(client); //Getting the number of choice from menu from the user.
        } catch (invalid_argument e) {
            //Not receiving so client disconnected
            //so listen to the next client
            server.listenServer();
            server.acceptServer(client);
            server.receive(client);
        }
        int choice_number = stoi(choice);
        if (choice_number == 3) {
            commands[2]->Execute(server, client);

        }else if(0 < choice_number && choice_number < 6){
            commands[choice_number - 1]->Execute(server, client);
        }
        else {
            server.sendServer("Invalid choice", client);
        }
        server.sendMenu(client);
    }
}

int mainValidation(int numArguments, string s_Port) {
    int numPort = 0;
    //Validation of number of arguments
    if (numArguments != 2) {
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

