#include "Server.h"


//Constructor
Server::Server(int serverPort) : m_client_socket(0) {
    m_server_port = serverPort;
    m_socket = getSocket();
    //Initializing the struct and adding values.
    memset(&m_sin, 0, sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = INADDR_ANY;
    m_sin.sin_port = htons(serverPort);
    //Initializing the client's struct without values.
    memset(&m_client_sin, 0, sizeof(m_client_sin));
    this->lastIndexInMap = 0;
    this->currentThreadIndex = 0;
}

//Creating and getting a socket.
int Server::getSocket() throw() {
    //Creating new socket
    int s = socket(AF_INET, SOCK_STREAM, 0);

    //Checking if the socket is not valid
    if (s < 0) {
        this->closeServer();
        throw invalid_argument("error creating socket");
    }
    return s;
}

//Binding the socket
void Server::bindServer() throw() {
    if (bind(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin)) < 0) {
        this->closeServer();
        throw invalid_argument("error binding socket");
    }
}

//Listen to a socket
void Server::listenServer() throw() {
    if (listen(m_socket, 5) < 0) {
        this->closeServer();
        throw invalid_argument("error listening to a socket");
    }
}

//Accepting a client and saving the client's socket id
void Server::acceptServer(ActiveClient &client) throw() {
    cout << "Entered accept func" << endl;
    //Adding new active client and adding 1 to the last index
    //Giving the client the same index to know how to reach him.

    //Saving and accepting the clients socket
    unsigned int addr_len = sizeof(client.getSockStruct());
    sockaddr_in temp = client.getSockStruct();
    int client_socket = accept(m_socket, (struct sockaddr *) &temp, &addr_len);
    if (client_socket < 0) {
        this->closeServer();
        throw invalid_argument("error accepting client");
    }
    client.setClientSocket(client_socket);
    cout << "Accepted the client" << endl;
}

void Server::sendServer(string answer, ActiveClient &C) throw() {
    char *send_text = new char[answer.length() + 1];
    ::strcpy(send_text, answer.c_str());
    int send_bytes = send(C.getClientSocket(), (void *) send_text, 4096, 0);
    if (send_bytes < 0) {
        this->closeServer();
        throw invalid_argument("Could not send msg");
    }
    cout << "Server sent: \n" << send_text << endl;
}

void Server::closeServer() throw() {
    close(m_socket);
}

string Server::receive(ActiveClient &client) {
    char buffer[4096];
    ::memset(buffer, 0, 4096);
    unsigned int buffer_length = 4096;
    int read_bytes = recv(client.getClientSocket(), buffer, buffer_length, 0);
    if (read_bytes == 0) {
        this->closeServer();
        exit(1);
    } else if (read_bytes < 0) {
        this->closeServer();
        throw invalid_argument("error with the receiving");
    }
    cout << "I receive: " << buffer << endl;
    return buffer;
}

vector<double> Server::manipulateMSG(string msg) throw() {
    char temp[msg.length() + 1];
    strcpy(temp, msg.c_str());
    vector<double> row;
    string word;
    stringstream s(temp);
    //keep on separating the line with Comma's
    //until its empty
    while (getline(s, word, ' ')) {
        if (s.eof()) {
            break;
        }
        try {
            // add all the column data
            // of a row to a vector
            row.push_back(stod(word));
        } catch (invalid_argument e) {
            //we got to letter
            return row; //might be invalid, will crash in numberOfCalculation.
        }
    }
    return row;
}

//Returning the type of distance
distanceType Server::getDisType(string msg) {
    char temp[msg.length() + 1];
    strcpy(temp, msg.c_str());
    //getting the number of words in the message.
    int count = 0;
    for (int i = 0; msg[i] != '\0'; i++) {
        if (msg[i] == ' ') {
            count++;
        }
    }
    count -= 1; //decreasing because of the distance type and number of neighbours.
    const char s[2] = " ";
    char *token;
    token = strtok(temp, s);

    //looping until the 1 before the last word in msg
    for (int i = 0; i < count; i++) {
        token = strtok(NULL, s);
    }
    try {
        return numberOfCalculation(token);
    } catch (invalid_argument e) {
        throw invalid_argument("invalid input");
    }
}

string Server::getDisTypeString(distanceType d) {
    try {
        switch (d) {
            case AUC:
                return "AUC";
            case MAN:
                return "MAN";
            case CHB:
                return "CHB";
            case MIN:
                return "MIN";
            case CAN:
                return "CAN";
        }
        //because did not return at all
        throw invalid_argument("Invalid distanceType");
    } catch (invalid_argument e) {
        throw invalid_argument("Invalid distanceType");
    }
}

//Returning the number of neighbours
int Server::getNumNeighbours() throw() {
    char temp[4096];
    strcpy(temp, msg);
    //getting the number of words in the message.
    int count = 0;
    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] == ' ') {
            count++;
        }
    }
    const char s[2] = " ";
    char *token;
    token = strtok(temp, s);

    //looping until the 1 before the last word in msg
    for (int i = 0; i < count; i++) {
        token = strtok(NULL, s);
    }
    return atoi(token);

}

void Server::closeClient() {
    //Do some stuff
    this->clients.erase(this->currentThreadIndex);
    //Delete and Exit this thread
}

void Server::sendMenu(ActiveClient &client) {
    first_command c1 = first_command();
    second_command c2 = second_command();
    third_command c3 = third_command();
    fourth_command c4 = fourth_command();
    fifth_command c5 = fifth_command();
    Command *arr[5] = {&c1, &c2, &c3, &c4, &c5};
    string menu = "";
    for (int i = 0; i < 5; ++i) {
        menu += to_string(i + 1) + ") " + arr[i]->get_desc() + "\n";
    }
    char *buffer = new char[menu.length() + 1];
    strcpy(buffer, menu.c_str());
    sendServer(buffer, client);
}
