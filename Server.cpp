#include "Server.h"

//Constructor
Server::Server(int serverPort,int socket): m_client_socket(0) {
    m_server_port = serverPort;
    m_socket = socket;
    //Initializing the struct and adding values.
    memset(&m_sin, 0, sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = INADDR_ANY;
    m_sin.sin_port = htons(serverPort);
    //Initializing the client's struct without values.
    memset(&m_client_sin, 0, sizeof(m_client_sin));
}
//Creating and getting a socket.
void Server::getSocket() throw() {
    //Creating new socket
    int socket = socket(AF_INET, SOCK_STREAM, 0);

    //Checking if the socket is not valid
    if(socket < 0){
        throw invalid_argument("error creating socket");
    }
    return socket;
}
//Binding the socket
void Server::bind() throw() {
    if(bind(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin)) < 0){
        throw invalid_argument("error binding socket");
    }
}
//Listen to a socket
void Server::listen() throw() {
    if(listen(m_socket, 5) < 0){
        throw invalid_argument("error listening to a socket");
    }
}
//Accepting a client and saving the client's socket id
void Server::accept() throw() {
    //Saving and accepting the clients socket
    m_client_socket = accept(m_socket,(struct sockaddr *) &m_client_sin, sizeof(m_client_sin));
    if(m_client_socket < 0){
        throw invalid_argument("error accepting client");
    }
}

vector<double> Server::receive() throw() {
    vector<double> my_vector;
    char buffer[4096];
    int read_bytes = recv(m_client_socket, buffer, sizeof(buffer), 0);
    if(read_bytes == 0){
        throw invalid_argument("need to close the connection because read_bytes = 0");
    }
    else if(read_bytes < 0){
        throw invalid_argument("error with the receiving");
    }
    for (int i = 0; i < sizeof(buffer); ++i) {
        my_vector.at[i] = buffer[i];  //Not supposed to work
    }
    return my_vector;
}

void Server::send() throw() {
    string buffer = "This message has been sent.";
    int send_bytes = send(m_client_socket, buffer, sizeof(buffer), 0);
}
