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
int Server::getSocket(){
    //Creating new socket
    int s = socket(AF_INET, SOCK_STREAM, 0);

    //Checking if the socket is not valid
    if (s < 0) {
        this->closeServer();
        throw exception();
    }
    return s;
}

//Binding the socket
void Server::bindServer() {
    if (bind(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin)) < 0) {
        this->closeServer();
        throw exception();
    }
}

//Listen to a socket
void Server::listenServer()  {
    if (listen(m_socket, 5) < 0) {
        this->closeServer();
        throw exception();
    }
}

//Accepting a client and saving the client's socket id
void Server::acceptServer(CLI &client)  {
    cout << "Entered accept func" << endl;
    //Adding new active client and adding 1 to the last index
    //Giving the client the same index to know how to reach him.

    //Saving and accepting the clients socket
    unsigned int addr_len = sizeof(client.getSockStruct());
    sockaddr_in temp = client.getSockStruct();
    int client_socket = accept(m_socket, (struct sockaddr *) &temp, &addr_len);
    if (client_socket < 0) {
        this->closeServer();
        throw exception();
    }
    client.setClientSocket(client_socket);
    cout << "Accepted the client" << endl;
}

void Server::sendServer(string answer, CLI &C) {
    char *send_text = new char[answer.length() + 1];
    ::strcpy(send_text, answer.c_str());
    int send_bytes = send(C.getClientSocket(), (void *) send_text, 200, 0);
    if (send_bytes < 0) {
        this->closeServer();
        throw exception();
    }
    cout << "This is what i sent: " << send_text << endl;
}

void Server::closeServer() {
    close(m_socket);
}

string Server::receive(CLI &client) {
    char buffer[200];
    ::memset(buffer, 0, 200);
    unsigned int buffer_length = 200;
    int read_bytes = recv(client.getClientSocket(), buffer, buffer_length, 0);
    if (read_bytes == 0) {
        this->closeServer();
        exit(1);
    } else if (read_bytes < 0) {
        this->closeServer();
        throw exception();
    }

    cout << "i got: " << buffer << endl;
    return buffer;
}

vector<double> Server::manipulateMSGWIthType(string msg){
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
        } catch (exception e) {
            //we got to letter
            return row; //might be invalid, will crash in numberOfCalculation.
        }
    }
    return row;
}

vector<double> Server::manipulateMSGWithoutType(string msg) {
    char temp[msg.length() + 1];
    strcpy(temp, msg.c_str());
    vector<double> row;
    string word;
    stringstream s(temp);
    //keep on separating the line with Comma's
    //until its empty
    while (getline(s, word, ' ')) {
        try {
            // add all the column data
            // of a row to a vector
            row.push_back(stod(word));
        } catch (exception e) {
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
    } catch (exception e) {
        throw exception();
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
        throw exception();
    } catch (exception e) {
        throw exception();
    }
}

//Returning the number of neighbours
int Server::getNumNeighbours(){
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

void Server::sendMenu(CLI &client) {
string menu = "welcome to KNN Classifier Server. Please choose an option:\n"
              "1. upload an unclassified csv data file\n"
              "2. algorithm settings\n"
              "3. classify data\n"
              "4. display results\n"
              "5. download results\n"
              "8. exit\n";
    char *buffer = new char[menu.length() + 1];
    strcpy(buffer, menu.c_str());
    sendServer(buffer, client);
}

int Server::getPortNumber() {
    return this->m_server_port;
}