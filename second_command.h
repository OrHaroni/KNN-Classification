#include "Command.h"
#include "string"
#ifndef ADVANCEDPROGPROJECT_SECOND_COMMAND_H
#define ADVANCEDPROGPROJECT_SECOND_COMMAND_H


using namespace std;

class second_command : public Command{
private:
    string m_description = "algorithm setting";

public:
    void Execute();

};



#endif //ADVANCEDPROGPROJECT_SECOND_COMMAND_H
