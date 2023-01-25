#include <iostream>
#include <pthread.h>
#include "Server.h"
#include "tableVec.h"
#include "FileVector.h"


using namespace std;

struct server_struct {
    Server& s;
    CLI& client;
};

int mainValidation(int, string);

void *handleClient(void *);

int main(int argc, char *argv[]) {
    pthread_t threads_arr[5];
    int portNumber = 0;
    //Checking validation of the arguments.
    try {
        portNumber = mainValidation(argc, argv[1]);
    } catch (invalid_argument e) {
        cout << e.what() << endl;
        return 1;
    }
    //Opening a server.
    Server server = Server(portNumber);
    server.bindServer();
    server.listenServer();
    while (true) {
        FileVector classified_db = FileVector();
        FileVector unclassified_db = FileVector();
        CLI client = CLI(&classified_db, &unclassified_db, server.getPortNumber(), 1);
        server_struct serverStruct = {server, client};
        for (int i = 0; i < 5; ++i) {
            server.acceptServer(client);
            pthread_create(&threads_arr[i], NULL, handleClient, &serverStruct);
        }
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

void *handleClient(void *serverStruct) {
    //We used auto but it will be server_strcut*
    auto *args = (server_struct *) serverStruct;
    Server server = args->s;
    CLI client = args->client;
    //Creating a vector of table vectors for future compares.
    first_command c1 = first_command(server, client);
    second_command c2 = second_command(server, client);
    third_command c3 = third_command(server, client);
    fourth_command c4 = fourth_command(server, client);
    fifth_command c5 = fifth_command(server, client);
    Command *commands[5] = {&c1, &c2, &c3, &c4, &c5};
    try {
        server.sendMenu(client);
    } catch (invalid_argument e) {
        server.sendServer("Invalid input", client);
    }
    string choice;
    int choice_number;
    while (true) {
        try {
            choice = server.receive(client); //Getting the number of choice from menu from the user.
            choice_number = stoi(choice);
        } catch (invalid_argument e) {
            choice_number = -1;
        }
        if (choice_number == 8) {
            pthread_exit(NULL);
        } else if (0 < choice_number && choice_number < 6) {
            commands[choice_number - 1]->Execute();

        } else if (choice_number != -1) {
            server.sendServer("Invalid choice, please try again", client);
        }
        server.sendMenu(client);
    }
}
