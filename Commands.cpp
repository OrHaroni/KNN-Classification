#include "Commands.h"
#include "Server.h"
#include "FileVector.h"

class Server;

class FileVector;

first_command::first_command() : Command("upload an unclassified csv data file") {
}

void first_command::Execute(Server* s, FileVector* vectors, FileVector* extra) {
    cout << "First command start" << endl;
    string s_vector = s->receive();
    string type_name = s->receive();
    char *temp = new char[s_vector.length() + 1];
    strcpy(temp, s_vector.c_str());
    cout << "This is vector before the loop" << temp << endl;
    while (::strcmp(temp, "-1")) {
        vector<double> temp_vec = s->manipulateMSG(temp);
        vectors->Add(tableVec(temp_vec, type_name));

        s_vector = s->receive();
        type_name = s->receive();
        ::memset(temp, 0, 4096);
        strcpy(temp, s_vector.c_str());
        cout << "This is temp" << temp << endl;
    }
    cout << "First command ended" << endl;
}

second_command::second_command() : Command("algorithm settings") {}

void second_command::Execute(Server* s, FileVector* vectors, FileVector* extra) {
    string send_s = "The current KNN parameters: K = " + to_string(vectors->getK()) + ", distance metric = " +
                    s->getDisTypeString(vectors->getDistanceType()) + "\n";
    char *temp_send = new char[send_s.length() + 1];
    ::strcpy(temp_send, send_s.c_str());
    s->sendServer(temp_send); //Sending the data
    string MinusOne = "-1";
    string temp_s = s->receive(); // Getting the value for k and Distance Type
    if (!temp_s.compare(MinusOne)) {
        cout << "we got -1 and sending 0, temp_s = " << temp_s;
        s->sendServer("0");
        return;
    } else {
        string word;
        char* wholeSentence = new char[temp_s.length() + 1];
        ::strcpy(wholeSentence, temp_s.c_str());
        word = strtok(wholeSentence," ");
        try {
            //Update the new K, if invalid - throw.
            int numk = stoi(word);
            if (numk < 1) {
                s->sendServer("Invalid value for k");
            } else {
                vectors->setK(numk);
            }
        } catch (invalid_argument e) {
            s->sendServer("Invalid value for k");
        }
        try {
            string word;
            word = strtok(NULL," ");
            //Getting the new type, if invalid - throw.
            distanceType new_DisType = s->getDisType(word);
            vectors->setDistanceType(new_DisType);
        } catch (invalid_argument e) {
            s->sendServer("Invalid value for metric");
        }
    }
    //Client receive until gets 0.
    cout << "Ending the func" << endl;
    s->sendServer("0");
}

third_command::third_command() : Command("classify data") {}

void third_command::Execute(Server* s, FileVector* classified, FileVector* unClassified) {
    if (classified->isFileEmpty() || unClassified->isFileEmpty()) {
        s->sendServer("please upload data");
        return;
    }

}

fourth_command::fourth_command() : Command("display result") {}

void fourth_command::Execute(Server* s, FileVector* vectors, FileVector* extra) {}

fifth_command::fifth_command() : Command("download results") {}

void fifth_command::Execute(Server* s, FileVector* vectors, FileVector* extra) {}
