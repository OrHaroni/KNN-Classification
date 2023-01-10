#include "Command.h"
#include <string>
#ifndef ADVANCEDPROGPROJECT_THIRD_COMMAND_H
#define ADVANCEDPROGPROJECT_THIRD_COMMAND_H



using namespace std;

class third_command : public Command{
private:
    string m_description = "classify data";

public:
    void Execute();

};



#endif //ADVANCEDPROGPROJECT_THIRD_COMMAND_H
