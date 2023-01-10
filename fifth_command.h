#include "Command.h"
#include <string>
#ifndef ADVANCEDPROGPROJECT_FIFTH_COMMAND_H
#define ADVANCEDPROGPROJECT_FIFTH_COMMAND_H
using namespace std;

class fifth_command : public Command{
private:
    string m_description = "download result";

public:
    void Execute();

};

#endif //ADVANCEDPROGPROJECT_FIFTH_COMMAND_H
