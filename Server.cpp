#include "Server.h"

//Constructor
Server::Server(int serverPort): m_client_socket(0) {
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
int Server::getSocket() throw() {
    //Creating new socket
    int s = socket(AF_INET, SOCK_STREAM, 0);

    //Checking if the socket is not valid
    if(s < 0){
        throw invalid_argument("error creating socket");
    }
    return s;
}
//Binding the socket
void Server::bindServer() throw() {
    if(bind(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin)) < 0){
        throw invalid_argument("error binding socket");
    }
}
//Listen to a socket
void Server::listenServer() throw() {
    if(listen(m_socket, 5) < 0){
        throw invalid_argument("error listening to a socket");
    }
}
//Accepting a client and saving the client's socket id
void Server::acceptServer() throw() {
    //Saving and accepting the clients socket
    unsigned int addr_len = sizeof(m_client_sin);
    m_client_socket = accept(m_socket,(struct sockaddr *) &m_client_sin, &addr_len);
    if(m_client_socket < 0){
        throw invalid_argument("error accepting client");
    }
}

void Server::receive() throw() {
    char buffer[4096];
    unsigned int buffer_length = strlen(buffer);
    int read_bytes = recv(m_client_socket, buffer, buffer_length, 0);
    if(read_bytes == 0){
        throw invalid_argument("need to close the connection because read_bytes = 0");
    }
    else if(read_bytes < 0){
        throw invalid_argument("error with the receiving");
    }
    cout << "This is the message:" << buffer << endl;
}

void Server::sendServer() throw() {
    char buffer[] = "This message has been sent.";
    unsigned int addr_len = strlen(buffer);
    int send_bytes = send(m_client_socket, (void* ) buffer, addr_len, 0);
}

void Server::closeServer() throw() {
    close(m_socket);
}
