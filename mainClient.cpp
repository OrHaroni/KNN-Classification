#include "Client.h"
#include "FileVector.h"
using namespace std;
void test();
void firstOption(Client&);
void secondOption(Client&);
void thirdOption(Client&);
void fourthOption(Client&);
void fifthOption(Client&);
void getVector(Client&);
void sendVectorsFromFile(Client&, string);
void sendVectorsFromFileAndType(Client&, string);
int main(int argc, char *argv[]) {
    //test();
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
    //Getting the socket and Sin and connect to the server.
    cout << "socket " << endl;
    c.getNewSocket();
    cout << "sin " << endl;
    c.startSin();
    cout << "connect " << endl;
    c.clientConnect();
    cout << "connected " << endl;
//    c.sendString("1");
//    c.receive();
//    firstOption(c);
//    c.sendString("3");
//    c.receive();
//    thirdOption(c);
//    c.sendString("4");
//    c.receive();
//    fourthOption(c);
    while (true) {
        cin.clear();
        //Get the menu.
        cout << c.receive() << endl;
        string input_option;
        //Clear the buffer.

        cin >> input_option;
        //Send the selected option.
        c.sendString(input_option);
        int optionNun;
        try{
            //Make the reception to number.
            optionNun = stoi(input_option);
        }
        catch (invalid_argument e){
            optionNun = 0;
        }
        switch (optionNun) {
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
                //The option is a number but not from the options.
                cout << "Invalid option please try again.";
                break;
        }
    }
}
void firstOption(Client& c){
    cout << "begin of 1" << endl;
    //Get the classifieds file from the user.
    string local_file_train;
    cout << "Please upload your local train CSV file." << endl;
    cin >> local_file_train;
    //local_file_train = "datasets/iris/iris_classified.csv";
    sendVectorsFromFileAndType(c, local_file_train);
    //Doing the same process for the unclassified.
    string local_file;
   cout << "Please upload your local test CSV file." << endl;
    cin >> local_file;
    //local_file = "datasets/iris/iris_Unclassified.csv";
    sendVectorsFromFile(c, local_file);
    c.receive();
    cout << c.receive() << endl;
}

void secondOption(Client& c){
    cout << "begin of 2" << endl;
    //Receive The k and type of distance.
    cout << c.receive() << endl;
    string input;
    cin.ignore();
    getline(cin,input);
    //cout << "input 1:" << input << endl;
    //Send the k and / or  / not the distance type.
    c.sendString(input);
    string ans_from_ser = c.receive();
    //0 mean the server done sending.
    if(!ans_from_ser.compare("0")){
        return;
    }
    do
    {
        cout << ans_from_ser << endl;
        ans_from_ser = c.receive();
    }while(!ans_from_ser.compare("0"));
}
void thirdOption(Client& c){
    cout << "begin of 3" << endl;
    cout << c.receive() << endl;
}
void fourthOption(Client& c){
    cout << "begin of 4" << endl;
    //Print the info from the server.
    string input = "0";

    while (input.compare("Done.")) {
        input = c.receive();
        if(!input.compare("please upload data")){
            cout << "please upload data" << endl;
            return;
        }
        if(!input.compare("please classify the data")){
            cout << "please upload data" << endl;
            return;
        }
        cout << input << endl;
        c.sendString(input);
    }
    cout << "Done." << endl;
    cout << " exit 4" << endl;
}
void fifthOption(Client& c){
    cout << "begin of 5" << endl;
    string local_file_path;
    cout << "Please upload your path to the file." << endl;
    cin >> local_file_path;
    // Create and open a text file
    try {
        ofstream myFile(local_file_path);
        c.sendString("ready");
       // cout << c.receive() << endl;
        string input;
        while (input.compare("Done.") && myFile.is_open()) {
            input = c.receive();
            if(!input.compare("please upload data")){
                cout << "please upload data" << endl;
                myFile.close();
                return;
            }
            if(!input.compare("please classify the data")){
                cout << "please upload data" << endl;
                myFile.close();
                return;
            }
            myFile << input << endl;
            c.sendString(input);
        }
        // Close the file
        myFile.close();
    }
    catch(exception const& e){
        cout << "Problem opening and writhing the file." << endl;
    }
}

void sendVectorsFromFile(Client& c, string path){
    FileVector fileVector_train = FileVector();
    fileVector_train.InitializeByReadingFileNoType(path);
    int size = fileVector_train.getVectors().size();
    //Sending the vectors to the server.
    cout << "size is " << size << endl;
    for (int i = 0; i < size; ++i) {
        string vec_to_send;
        vec_to_send = fileVector_train.getVectors().at(i).to_string();
        c.sendString(vec_to_send);
        c.receive();
        //string str1 = c.receive();
       // cout  << " i sent " << vec_to_send << endl;
    }
    //Sending -1 to say rhe server we're done uploading.
    c.sendString("adarkatz");
}
void sendVectorsFromFileAndType(Client& c , string path){
    FileVector fileVector_train = FileVector();
    fileVector_train.InitializeByReadingFile(path);
    int size = fileVector_train.getVectors().size();
    cout << "size is " << size << endl;
    for (int i = 0; i < size; ++i) {
        string vec_to_send;
        vec_to_send = fileVector_train.getVectors().at(i).to_string();
        c.sendString(vec_to_send);
        c.receive();
        //string str1 = c.receive();
        //cout  << " i sent " << vec_to_send << endl;
        string vec_to_send_type;
        vec_to_send_type = fileVector_train.getVectors().at(i).getType();
        c.sendString(vec_to_send_type);
        c.receive();
        //string str2 = c.receive();
       // cout  << " i sent " << vec_to_send_type << endl;
    }
    //Sending -1 to say rhe server we're done uploading.
    c.sendString("adarkatz");
}

void test(){
    FileVector fileVector_train = FileVector();
    fileVector_train.InitializeByReadingFile("datasets/iris/iris_classified.csv");
    int size = fileVector_train.getVectors().size();
    int i;
    for (i = 0; i < size; ++i) {
        string vec_to_send;
        //vec_to_send = fileVector_train.getVectors().at(i).to_string();

        //cout  << " i sent " << vec_to_send << endl;
        string vec_to_send_type;
        vec_to_send_type = fileVector_train.getVectors().at(i).getType();

        cout  << " i sent " << vec_to_send_type << endl;
    }
    //Sending -1 to say rhe server we're done uploading.
}

