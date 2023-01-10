#ifndef ADVANCEDPROGPROJECT_FIRST_COMMAND_H
#define ADVANCEDPROGPROJECT_FIRST_COMMAND_H
#include "Command.h"
#include <string>

using namespace std;

class first_command : public Command{
private:
    //"upload an unclassified csv data file"

public:
    first_command(string);
    void Execute();

};


#endif //ADVANCEDPROGPROJECT_FIRST_COMMAND_H
