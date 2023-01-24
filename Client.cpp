#include "Client.h"
Client::Client(const char * ip_address,int port_no):m_ip_address(ip_address),m_port_no(port_no) {}

void Client::getNewSocket() throw(){
    //Get a new socket from the system.
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket < 0){
        throw invalid_argument("error creating socket");
    }
}



void Client::startSin(){
    //Start an s in.
    memset(&m_sin,0,sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = inet_addr(m_ip_address);
    m_sin.sin_port = htons(m_port_no);
}

void Client::clientConnect() throw(){
    //Connect to the server.
    int connect_num = connect(m_socket, (struct sockaddr *) &m_sin, sizeof(m_sin));
    if(connect_num < 0){
        throw invalid_argument("error in connect procces");
    }
}

void Client::sendString(string string1) throw() {
    if(string1.length() == 0){
        return;
    }

//    while (string1.length() <=200){
//        string1 += "$";
//    }
    //cout << "after dolaes: " << string1 << endl;
    const int len = string1.length();
    char *temp = new char[len + 1];
    strcpy(temp, string1.c_str());
    //cout << "I sent " << temp << " and len is " << strlen(temp) << endl;
    cout << " i send : " << string1 << endl;
    int sent_num = send(m_socket, (void *) temp, 200, 0);
    if (sent_num < 0) {
        throw invalid_argument("error in sending");
    }
    if (sent_num == 0) {
        cout << "i send empy" << endl;
    }
}

string Client::receive() throw(){

    char buffer[200];
    ::memset(buffer,0,200);
    unsigned int buffer_len = 200;
    int read_bytes = recv(m_socket, buffer, buffer_len, 0);
    if (strlen(buffer) == 0){
        read_bytes = recv(m_socket, buffer, buffer_len, 0);
    }
    if (strlen(buffer) == 0){
        read_bytes = recv(m_socket, buffer, buffer_len, 0);
    }
//    while(!strcmp(&buffer[strlen(buffer) - 1],"$")){
//        buffer[strlen(buffer) - 1] = 0;
//    }
    //If the size is zero we need to close.
    if (read_bytes == 0) {
        throw invalid_argument("close");
    }
    //If it's less than zero there is a problem.
    else if (read_bytes < 0){
        throw invalid_argument("error in receive");
    }
    else{
        //cout << "I received:" << buffer << "end of receive" << endl;
        return buffer;
    }
}
void Client::disconnect(){
    //Disconnect from the server.
    close(m_socket);
}