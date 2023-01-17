#include "Client.h"
#include "FileVector.h"
using namespace std;
void firstOption(Client);
void secondOption(Client);
void thirdOption(Client);
void fourthOption(Client);
void fifthOption(Client);
int main(int argc, char *argv[]) {
    //The number of args is 3.
    if (argc != 3) {
        return 1;
    }
    //Split the ip to numbers to check it.
    string port = argv[1];
    char seps[] = ".";
    char *token;
    token = strtok(&port[0], seps);
    while (token != NULL) {
        int number = 0;
        try {
            //Make it a number.
            number = stoi(token);
        }
        catch (invalid_argument e) {
            cout << "Invalid ip" << endl;
            return 0;
        }
        if (number < 0) {
            cout << "Invalid ip" << endl;
            return 1;
        }
        if (number > 256) {
            cout << "Invalid ip" << endl;
            return 1;
        }
        token = strtok(NULL, seps);

    }
    //Get the port number.
    int port_number = 0;
    try {
        port_number = stoi(argv[2]);
    } catch (invalid_argument e) {
        cout << "invalid size of port" << endl;
    }
    //If we got here it's a number.
    if (port_number < 1024 || port_number > 65535) {
        cout << "invalid size of port" << endl;
        return 1;
    }
    //Start the client with the port and ip.
    Client c = Client(argv[1], port_number);
    c.getNewSocket();
    c.startSin();
    c.clientConnect();
    while (true) {
        string toPrint = c.receive();
        cout << toPrint << endl;
        string input_option;
        getline(cin, input_option);
        const int len_option = input_option.length();
        char *temp_option = new char[len_option + 1];
        strcpy(temp_option, input_option.c_str());
        char *str_option = new char[2];
        strcpy(str_option, temp_option);
        c.sendVector(str_option);

        switch (stoi(input_option)) {
            case 1:
                firstOption(c);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
        }


    }
}
void firstOption(Client c){
    
}
void secondOption(Client c){
    string input;
    getline(cin,input);
    const int len = input.length();
    char *temp = new char[len+1];
    strcpy(temp,input.c_str());
    //If the string is -1 we exit.
    if(!strcmp(temp,"-1")){
        char* str = new char[2];
        strcpy(str,temp);
        c.sendVector(str);
        c.disconnect();
        return;
    }
    //Sent the vector.
    c.sendVector(temp);
    //        Print the type.
    //        Clear the buffer.
    cin.clear();
    cin.clear();
}
void thirdOption(Client c){

}
void fourthOption(Client c){

}
void fifthOption(Client c){

}