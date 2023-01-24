#include "Commands.h"
#include "Server.h"
#include "FileVector.h"

class Server;

class FileVector;

void sendVectorsFromFileAndType(Server &, ActiveClient &);

first_command::first_command() : Command("upload an unclassified csv data file") {}

void first_command::Execute(Server &s, ActiveClient &client) {
    vector<double> temp_vec;
    string s_vector = s.receive(client);
    s.sendServer(s_vector,client);
    string type_name = s.receive(client);
    s.sendServer(type_name,client);
    char *temp = new char[s_vector.length() + 1];
    strcpy(temp, s_vector.c_str());
    while (s_vector.compare("adarkatz")) {
        temp_vec = s.manipulateMSGWIthType(temp);
        tableVec temp_tablevec = tableVec(temp_vec, type_name);
        client.getClassified()->Add(temp_tablevec);
        s_vector = s.receive(client);
        s.sendServer(s_vector,client);
        type_name = s.receive(client);
        s.sendServer(type_name,client);
        strcpy(temp, s_vector.c_str());
    }
    client.getClassified()->upload_complete();
    s_vector = s.receive(client);
    strcpy(temp, s_vector.c_str());
    while (s_vector.compare("adarkatz")) {
        temp_vec = s.manipulateMSGWithoutType(temp);
        tableVec temp_tablevec = tableVec(temp_vec, " ");
        client.getUnClassified()->Add(temp_tablevec);
        s_vector = s.receive(client);
        strcpy(temp, s_vector.c_str());
        if (s_vector.compare("adarkatz")) {
            s.sendServer(s_vector, client);
        }
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
    distanceType typeClac = client.getDisType();
    for (int i = 0; i < unclassified_size; ++i) {
        FileVector temp_classified = FileVector(*client.getClassified());
        vector<double> main_vector = client.getUnClassified()->getVectors().at(i).getVector();
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
            if (maxType < neighbours.at(sorter.at(j).getType())) {
                maxType = neighbours.at(sorter.at(j).getType());
                maxTypeName = sorter.at(j).getType();
            }
        }
        client.getUnClassified()->setName(maxTypeName,i);
    }
    s.sendServer("classifying data complete", client);

}

fourth_command::fourth_command() : Command("display result") {}

void fourth_command::Execute(Server &s, ActiveClient &client) {
    int size = client.getUnClassified()->getVectors().size();
    string temp_output;
    cout << "This is the size: " << size << endl;
    for (int i = 0; i < size; ++i) {
        temp_output = to_string(i + 1) + "\t" + client.getUnClassified()->getVectors().at(i).getType();
        s.sendServer(temp_output, client);
        s.receive(client);
    }
    s.sendServer("Done.", client);
    s.receive(client);
}

fifth_command::fifth_command() : Command("download results") {}

void fifth_command::Execute(Server &s, ActiveClient &client) {
    sendVectorsFromFileAndType(s, client);
}

void sendVectorsFromFileAndType(Server &s, ActiveClient &client) {

    int size = client.getUnClassified()->getVectors().size();
    for (int i = 0; i < size; ++i) {
        string vec_to_send;
        vec_to_send = client.getUnClassified()->getVectors().at(i).to_string();
        s.sendServer(vec_to_send, client);
        s.receive(client);
        string str1 = s.receive(client);
        string vec_to_send_type;
        vec_to_send_type = client.getUnClassified()->getVectors().at(i).getType();
        s.sendServer(vec_to_send_type, client);
        s.receive(client);
        string str2 = s.receive(client);
    }
    //Sending -1 to say rhe server we're done uploading.
    s.sendServer("adarkatz", client);
}
