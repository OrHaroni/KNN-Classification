#ifndef ADVANCEDPROGPROJECT_COMMANDS_H
#define ADVANCEDPROGPROJECT_COMMANDS_H
#include "Command.h"
#include <string>



using namespace std;

class Server;

class first_command : public Command{
private:
    Server& server;
    CLI& client;
public:
    first_command(Server& , CLI&);
    void Execute();
};

class second_command : public Command{
private:
    Server& server;
    CLI& client;
public:
    second_command(Server& , CLI&);
    void Execute();
};

class third_command : public Command{
private:
    Server& server;
    CLI& client;
public:
    third_command(Server& , CLI&);
    void Execute();
};

class fourth_command : public Command{
private:
    Server& server;
    CLI& client;
public:
    fourth_command(Server& , CLI&);
    void Execute();
};

class fifth_command : public Command{
private:
    Server& server;
    CLI& client;
public:
    fifth_command(Server& , CLI&);
    void Execute();
};

#endif //ADVANCEDPROGPROJECT_COMMANDS_H