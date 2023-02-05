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
}

//Creating and getting a socket.
int Server::getSocket() {
    //Creating new socket
    int s = socket(AF_INET, SOCK_STREAM, 0);

    //Checking if the socket is not valid
    if (s < 0) {
        this->closeServer();
        cout << "error creating socket" << endl;
        throw exception();
    }
    return s;
}

//Binding the socket
void Server::bindServer()  {
    if (bind(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin)) < 0) {
        this->closeServer();
        cout << "error binding socket" << endl;
        throw exception();
    }
}

//Listen to a socket
void Server::listenServer(){
    if (listen(m_socket, 1) < 0) {
        this->closeServer();
        cout << " listening to a socket" << endl;
        throw exception();
    }
}

//Accepting a client and saving the client's socket id
void Server::acceptServer() {
    //Saving and accepting the clients socket
    unsigned int addr_len = sizeof(m_client_sin);
    m_client_socket = accept(m_socket, (struct sockaddr *) &m_client_sin, &addr_len);
    if (m_client_socket < 0) {
        this->closeServer();
        cout << "error accepting client" << endl;
        throw exception();
    }
}

void Server::sendServer(char* answer) {
    int send_bytes = send(m_client_socket, (void *) answer, 4096, 0);
    if (send_bytes < 0) {
        this->closeServer();
        cout << "Could not send msg" << endl;
        throw exception();
    }
}

void Server::closeServer()  {
    close(m_socket);
}

void Server::receive() {
    char buffer[4096];
    ::memset(buffer,4096,1);
    unsigned int buffer_length = 4096;
    int read_bytes = recv(m_client_socket, buffer, buffer_length, 0);
    //get rid of unnecessary char in the last place.
    if (buffer[strlen(buffer) - 1] > '9' || buffer[strlen(buffer) - 1] <= '0') {
        buffer[strlen(buffer) - 1] = 0; // get rid of unnecessary char.
    }
    if (read_bytes == 0) {
        this->closeServer();
        exit(1);
    } else if (read_bytes < 0) {
        this->closeServer();
        cout << "error with the receiving" << endl;
        throw exception();
    }
    strcpy(msg, buffer);
    if(msg[0] == '-' && msg[1] == '1'){
        throw exception();
    }
}

vector<double> Server::manipulateMSG() {
    char temp[strlen(msg)];
    strcpy(temp, msg);
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

//Returning the type of distance
distanceType Server::getDisType() {
    char temp[4096];
    strcpy(temp, msg);
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
    }catch (exception e){
        cout << "invalid input" << endl;
        throw exception();
    }
}

//Returning the number of neighbours
int Server::getNumNeighbours() {
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
