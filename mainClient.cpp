#include "Client.h"
#include <limits>
using namespace std;

int main(int argc, char *argv[]){

    Client c = Client("172.18.48.181",12335);
    c.getNewSocket();
    c.startSin();
    c.clientConnect();

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
            return 0;
        }
        c.sendVector(temp);
        string toPrint = c.receive();
        cout << toPrint << endl;
        cin.clear();
        cin.clear();
    }
}