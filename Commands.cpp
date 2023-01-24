#include "Commands.h"
#include "Server.h"
#include "FileVector.h"

class Server;

class FileVector;

void sendClassificationToClient(Server &, CLI &);

first_command::first_command(Server &s, CLI &client) : Command("upload an unclassified csv data file"), server(s),
                                                       client(client) {}

void first_command::Execute() {
    vector<double> temp_vec;
    string s_vector = server.receive(client);
    server.sendServer(s_vector, client);
    string type_name = server.receive(client);
    server.sendServer(type_name, client);
    char *temp = new char[s_vector.length() + 1];
    strcpy(temp, s_vector.c_str());
    while (s_vector.compare("adarkatz")) {
        temp_vec = server.manipulateMSGWIthType(temp);
        tableVec temp_tablevec = tableVec(temp_vec, type_name);
        client.getClassified()->Add(temp_tablevec);
        s_vector = server.receive(client);
        server.sendServer(s_vector, client);
        type_name = server.receive(client);
        server.sendServer(type_name, client);
        strcpy(temp, s_vector.c_str());
    }
    client.getClassified()->upload_complete();
    s_vector = server.receive(client);
    server.sendServer(s_vector, client);
    strcpy(temp, s_vector.c_str());
    while (s_vector.compare("adarkatz")) {
        temp_vec = server.manipulateMSGWithoutType(temp);
        tableVec temp_tablevec = tableVec(temp_vec, " ");
        client.getUnClassified()->Add(temp_tablevec);
        s_vector = server.receive(client);
        strcpy(temp, s_vector.c_str());
        if (s_vector.compare("adarkatz")) {
            server.sendServer(s_vector, client);
        }
    }
    client.getUnClassified()->upload_complete();
    server.sendServer("Upload complete.", client);
}

second_command::second_command(Server &s, CLI &client) : server(s), client(client), Command("algorithm settings") {}

void second_command::Execute() {
    string send_s = "The current KNN parameters: K = " + to_string(client.getKNumber()) + ", distance metric = " +
                    server.getDisTypeString(client.getDisType()) + "\n";
    char *temp_send = new char[send_s.length() + 1];
    ::strcpy(temp_send, send_s.c_str());
    server.sendServer(temp_send, client); //Sending the data
    string MinusOne = "-1";
    string temp_s = server.receive(client); // Getting the value for k and Distance Type
    if (!temp_s.compare(MinusOne)) {
        server.sendServer("0", client);
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
                server.sendServer("Invalid value for k", client);
            } else {
                client.setKNumber(numk);
            }
        } catch (invalid_argument e) {
            server.sendServer("Invalid value for k", client);
        }
        try {
            if (word != NULL) {
                word = strtok(NULL, " ");
                if (word != NULL) {
                    //Getting the new type, if invalid - throw.
                    distanceType new_DisType = server.getDisType(word);
                    client.setDisType(new_DisType);
                }
            }

        } catch (invalid_argument e) {
            server.sendServer("Invalid value for metric", client);
        }
    }
    //Client receive until gets 0.
    server.sendServer("0", client);
}

third_command::third_command(Server &s, CLI &client) : server(s), client(client), Command("classify data") {}

void third_command::Execute() {
    //If there is not any data
    if (client.getClassified()->isFileEmpty() || client.getUnClassified()->isFileEmpty()) {
        server.sendServer("please upload data", client);
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
        client.getUnClassified()->setName(maxTypeName, i);
    }
    server.sendServer("classifying data complete", client);
    client.classifyTheData();
}

fourth_command::fourth_command(Server &s, CLI &client) : server(s), client(client), Command("display result") {}

void fourth_command::Execute() {
    sendClassificationToClient(server, client);
}

fifth_command::fifth_command(Server &s, CLI &client) : server(s), client(client), Command("download results") {}

void fifth_command::Execute() {
    string StartUpload = server.receive(client);
    sendClassificationToClient(server, client);
}

void sendClassificationToClient(Server &s, CLI &client) {
    //If there is not any data
    if (client.getClassified()->isFileEmpty() || client.getUnClassified()->isFileEmpty()) {
        s.sendServer("please upload data", client);
        return;
    }
    if (!client.isClassifiedTheData()) {
        s.sendServer(("please classify the data"), client);
        return;
    }
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
