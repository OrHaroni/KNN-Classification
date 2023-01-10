#include "Command.h"
#include <string>
#ifndef ADVANCEDPROGPROJECT_FIRST_COMMAND_H
#define ADVANCEDPROGPROJECT_FIRST_COMMAND_H
using namespace std;

class first_command : public Command{
private:
    string m_description = "upload an unclassified csv data file";

public:
    void Execute();
};


#endif //ADVANCEDPROGPROJECT_FIRST_COMMAND_H
