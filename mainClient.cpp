#include "Client.h"
#include "FileVector.h"
using namespace std;
void firstOption(Client);
void secondOption(Client);
void thirdOption(Client);
void fourthOption(Client);
void fifthOption(Client);
void getVector(Client c);
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
        int number;
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
    cout << "connected" << endl;
    while (true) {
        string toPrint = c.receive(); //Get the menu.
        cout << toPrint << endl;
        string input_option;
        cin.clear();
        cin >> input_option;
        c.sendVector(input_option);
        switch (stoi(input_option)) {
            case 1:
                firstOption(c);
                break;
            case 2:
                secondOption(c);
                break;
            case 3:
                thirdOption(c);
                break;
            case 4:
                fourthOption(c);
                break;
            case 5:
                fifthOption(c);
                break;
            case 8:
                c.disconnect();
                return 0;
            default:
                cout << "Invalid option please try again.";
                break;
        }
    }
}
void firstOption(Client c){
    string local_file_train;
    cout << "Please upload your local train CSV file." << endl;
    cin >> local_file_train;
    FileVector fileVector_train = FileVector();
    fileVector_train.InitializeByReadingFile(local_file_train);
    int vecSize_train  = fileVector_train.SizeOfVectors();
    for (int i = 0; i < vecSize_train; ++i) {
        string vec_to_send;
        vec_to_send = fileVector_train.getVectors().at(i).to_string();
        c.sendVector(vec_to_send);
        cout  << " i sent " << vec_to_send << endl;
        string vec_to_send_type;
        vec_to_send_type = fileVector_train.getVectors().at(i).getType();
        c.sendVector(vec_to_send_type);
        cout  << " i sent " << vec_to_send_type << endl;
    }
    c.sendVector("-1");
    string local_file;
    cout << "Please upload your local test CSV file." << endl;
    cin >> local_file;
    FileVector fileVector = FileVector();
    fileVector.InitializeByReadingFile(local_file);
    int vecSize  = fileVector.SizeOfVectors();
    for (int i = 0; i < vecSize; ++i) {
        string vec_to_send;
        vec_to_send = fileVector.getVectors().at(i).to_string();
        c.sendVector(vec_to_send);
        cout  << " i sent " << vec_to_send << endl;
        string vec_to_send_type;
        vec_to_send_type = fileVector.getVectors().at(i).getType();
        c.sendVector(vec_to_send_type);
        cout  << " i sent " << vec_to_send_type << endl;
    }
    c.sendVector("-1");
    cout << c.receive() << endl;
}

void secondOption(Client c){
    cout << "begin of 2" << endl;
    cout << c.receive() << endl;
    string input;
    cin.ignore();
    getline(cin,input);
    cout << "input 1:" << input << endl;
    c.sendVector(input);
    string ans_from_ser = c.receive();
    while(ans_from_ser.compare("0")){
        cout << ans_from_ser << endl;
        ans_from_ser = c.receive();
    }
    cout << "end of func" << endl;
}
void thirdOption(Client c){
    cout << c.receive() << endl;
}
void fourthOption(Client c){

}
void fifthOption(Client c){

}

