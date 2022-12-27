#include "Client.h"
Client::Client(const char * ip_address,int port_no):m_ip_address(ip_address),m_port_no(port_no) {}

int Client::getNewSocket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

void Client::setSocket(int socket) {
    m_socket = socket;
}

void Client::startSin(){
    memset(&m_sin,0,sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = inet_addr(m_ip_address);
    m_sin.sin_port = htons(m_port_no);
}

int Client::clientConnect() {
    return connect(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin));
}

int Client::sendVector(vector<double> vector){
    char data_addr[] = "Im a message";
    return send(m_socket, data_addr, strlen(data_addr), 0);
}
string Client::receive(){
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_socket, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
// connection is closed
    }
    else if (read_bytes < 0) {
// error
    }
    else {
        cout << buffer;
    }
}



