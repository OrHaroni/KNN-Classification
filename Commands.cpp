#include "Commands.h"
#include "Server.h"
#include "FileVector.h"

class Server;

class FileVector;

first_command::first_command() : Command("upload an unclassified csv data file") {
}

void first_command::Execute(Server s, FileVector vectors) {
    string answer = s.receive();
    string type_name = s.receive();
    char *temp = new char[answer.length() + 1];
    strcpy(temp, answer.c_str());
    while(::strcmp(temp, "-1")){
        vector<double> temp_vec = s.manipulateMSG(temp);
        vectors.Add(tableVec(temp_vec, type_name));

        answer = s.receive();
        type_name = s.receive();
        strcpy(temp, answer.c_str());
    }

}

second_command::second_command() : Command("algorithm settings") {}

void second_command::Execute(Server s, FileVector vectors) {
    string send_s = "The current KNN paramaters: K = " + to_string(vectors.getK()) + ", distance metric = " + s.getDisTypeString(vectors.getDistanceType()) + "\n";
}

third_command::third_command() : Command("classify data") {}

void third_command::Execute(Server s, FileVector vectors) {}

fourth_command::fourth_command() : Command("display result") {}

void fourth_command::Execute(Server s, FileVector vectors) {}

fifth_command::fifth_command() : Command("download results") {}

void fifth_command::Execute(Server s, FileVector vectors) {}
