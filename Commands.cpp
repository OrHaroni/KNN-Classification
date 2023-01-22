#include "Commands.h"
#include "Server.h"
#include "FileVector.h"

class Server;

class FileVector;

first_command::first_command() : Command("upload an unclassified csv data file") {
}

void first_command::Execute(Server &s, ActiveClient &client) {
    vector<double> temp_vec;
    cout << "First command start" << endl;
    string s_vector = s.receive(client);
    s.sendServer(s_vector, client);
    string type_name = s.receive(client);
    s.sendServer(type_name, client);
    char *temp = new char[s_vector.length() + 1];
    strcpy(temp, s_vector.c_str());
    while (s_vector.compare("adarkatz")) {
        temp_vec = s.manipulateMSG(temp);
        client.getClassified()->Add(tableVec(temp_vec, type_name));
        s_vector = s.receive(client);
        s.sendServer(s_vector, client);
        type_name = s.receive(client);
        s.sendServer(type_name, client);
    }
    client.getClassified()->upload_complete();
    cout << "end of func" << endl;
    cout << "First command end upload first classified" << endl;
    s_vector = s.receive(client);
    s.sendServer(s_vector,client);
    strcpy(temp, s_vector.c_str());
    cout << "This is vector before the loop" << temp << endl;
    while (s_vector.compare("adarkatz")) {
        vector<double> temp_vec = s.manipulateMSG(temp);
        client.getUnClassified()->Add(tableVec(temp_vec, " "));
        s_vector = s.receive(client);
        s.sendServer(s_vector,client);
    }
    client.getUnClassified()->upload_complete();
    s.sendServer("Upload complete.", client);
}

second_command::second_command() : Command("algorithm settings") {}

void second_command::Execute(Server &s, ActiveClient &client) {
    string send_s = "The current KNN parameters: K = " + to_string(client.getKNumber()) + ", distance metric = " +
                    s.getDisTypeString(client.getDisType()) + "\n";
    char *temp_send = new char[send_s.length() + 1];
    ::strcpy(temp_send, send_s.c_str());
    s.sendServer(temp_send, client); //Sending the data
    string MinusOne = "-1";
    string temp_s = s.receive(client); // Getting the value for k and Distance Type
    if (!temp_s.compare(MinusOne)) {
        s.sendServer("0", client);
        return;
    } else {
        char *word;
        char *wholeSentence = new char[temp_s.length() + 1];
        ::strcpy(wholeSentence, temp_s.c_str());
        word = strtok(wholeSentence, " ");
        try {
            //Update the new K, if invalid - throw.
            int numk = stoi(word);
            if (numk < 1) {
                s.sendServer("Invalid value for k", client);
            } else {
                client.setKNumber(numk);
            }
        } catch (invalid_argument e) {
            s.sendServer("Invalid value for k", client);
        }
        try {
            if (word != NULL) {
                word = strtok(NULL, " ");
                if (word != NULL) {
                    //Getting the new type, if invalid - throw.
                    distanceType new_DisType = s.getDisType(word);
                    client.setDisType(new_DisType);
                }
            }

        } catch (invalid_argument e) {
            s.sendServer("Invalid value for metric", client);
        }
    }
    //Client receive until gets 0.
    s.sendServer("0", client);
}

third_command::third_command() : Command("classify data") {}

void third_command::Execute(Server &s, ActiveClient &client) {
    if (client.getClassified()->isFileEmpty() || client.getUnClassified()->isFileEmpty()) {
        s.sendServer("please upload data", client);
        return;
    }
    const vector<tableVec> temp_tableVec = client.getUnClassified()->getVectors();
    int unclassified_size = client.getUnClassified()->getVectors().size();
    int classified_size = client.getClassified()->getVectors().size();
    FileVector temp_classified;
    vector<double> main_vector;
    distanceType typeClac = client.getDisType();
    for (int i = 0; i < unclassified_size; ++i) {
        temp_classified = FileVector(&temp_tableVec);
        main_vector = client.getUnClassified()->getVectors().at(i).getVector();
        for (int j = 0; j < classified_size; ++j) {
            temp_classified.getVectors().at(j).calcDis(main_vector, typeClac);
        }
        vector<tableVec> sorter = temp_classified.getVectors();
        sort(sorter.begin(), sorter.end(), compareDistance);
        //Iterator to count how many times each type is there
        map<string, int> neighbours;
        for (int j = 0; j < client.getKNumber(); ++j) {
            addToMap(neighbours, sorter.at(j));
        }
        //Checking the largest.
        int maxType = 0;
        string maxTypeName = sorter.at(0).getType();
        for (int j = 0; j < neighbours.size(); ++j) {
            if (maxType < neighbours.at(sorter.at(i).getType())) {
                maxType = neighbours.at(sorter.at(i).getType());
                maxTypeName = sorter.at(i).getType();
            }
        }
        client.getUnClassified()->getVectors().at(i).setStringType(maxTypeName);
    }
    s.sendServer("classifying data complete", client);
}

fourth_command::fourth_command() : Command("display result") {}

void fourth_command::Execute(Server &, ActiveClient &) {

}

fifth_command::fifth_command() : Command("download results") {}

void fifth_command::Execute(Server &, ActiveClient &) {}
