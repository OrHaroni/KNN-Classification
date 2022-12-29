#include "Client.h"
Client::Client(const char * ip_address,int port_no):m_ip_address(ip_address),m_port_no(port_no) {}

int Client::getNewSocket() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket < 0){
        throw invalid_argument("error creating socket");
    }
}



void Client::startSin(){
    memset(&m_sin,0,sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = inet_addr(m_ip_address);
    m_sin.sin_port = htons(m_port_no);
}

void Client::clientConnect() {
    int connect_num = connect(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin));
    if(connect_num < 0){
        throw invalid_argument("error in connect procces");
    }

}

void Client::sendVector(){
    char data_addr[] = "Im a message";
    int sent_num = send(m_socket, data_addr, strlen(data_addr), 0);
    if(sent_num < 0){
        throw invalid_argument("error in sending");
    }
}
string Client::receive(){
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_socket, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        throw invalid_argument("close");
    }
    else if (read_bytes < 0){
        throw invalid_argument("error in receive");
    }
    else{
        return buffer;
    }
}



