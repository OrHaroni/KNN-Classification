#include "Client.h"
#include <limits>
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        return 1;
    }
    string port = argv[1];
    char seps[] = ".";
    char *token;
    token = strtok( &port[0], seps );
    while( token != NULL )
    {
        int number = 0;
        try{
            number = stoi(token);
        }
        catch(invalid_argument e) {
            cout << "Invalid ip" << endl;
            return 0;
        }
        if (number < 0){
            cout << "Invalid ip" << endl;
            return 1;
        }
        if (number > 256){
            cout << "Invalid ip" << endl;
            return 1;
        }
        token = strtok( NULL, seps );
        cout << "after token" << endl;
    }
    int port_number = 0;
    try{
        port_number = stoi(argv[2]);
    }catch(invalid_argument e){
        cout << "invalid size of port" << endl;
    }
    //If we got here it's a number.
    if(port_number < 1024 || port_number > 65535){
        cout << "invalid size of port" << endl;
        return 1;
    }
    cout << "after port val" << endl;

    cout << argv[1] << endl;
    cout << port_number << endl;

    Client c = Client(argv[1],port_number);
    c.getNewSocket();
    cout << "got soc" << endl;
    c.startSin();
    cout << "got sin" << endl;
    c.clientConnect();
    cout << "connected" << endl;
    while (true){

        string input;
        getline(cin,input);
        const int len = input.length();
        char *temp = new char[len+1];
        strcpy(temp,input.c_str());
        if(!strcmp(temp,"-1")){
            char* str = new char[2];
            strcpy(str,temp);
            c.sendVector(str);
            c.disconnect();
            return 1;
        }
        c.sendVector(temp);
        cout<< "sent" << temp << endl;
        string toPrint = c.receive();
        cout << toPrint << endl;
        cin.clear();
        cin.clear();
    }
}