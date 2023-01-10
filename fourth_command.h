#include "Command.h"
#include <string>
#ifndef ADVANCEDPROGPROJECT_FOURTH_COMMAND_H
#define ADVANCEDPROGPROJECT_FOURTH_COMMAND_H

using namespace std;

class fourth_command : public Command{
private:
    string m_description = "display result";

public:
    void Execute();
};

#endif //ADVANCEDPROGPROJECT_FOURTH_COMMAND_H
