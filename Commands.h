#ifndef ADVANCEDPROGPROJECT_COMMANDS_H
#define ADVANCEDPROGPROJECT_COMMANDS_H
#include "Command.h"
#include <string>



using namespace std;

class Server;

class first_command : public Command{
public:
    first_command();
    void Execute(Server& , ActiveClient&);
};

class second_command : public Command{
public:
    second_command();
    void Execute(Server& , ActiveClient&);
};

class third_command : public Command{
public:
    third_command();
    void Execute(Server& , ActiveClient&);
};

class fourth_command : public Command{
public:
    fourth_command();
    void Execute(Server& , ActiveClient&);
};

class fifth_command : public Command{
public:
    fifth_command();
    void Execute(Server& , ActiveClient&);
};

#endif //ADVANCEDPROGPROJECT_COMMANDS_H