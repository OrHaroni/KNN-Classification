#ifndef ADVANCEDPROGPROJECT_COMMAND_H
#define ADVANCEDPROGPROJECT_COMMAND_H

#include <stdio.h>
#include <string>

using namespace std;
class Server;
class FileVector;

class Command {
private:
    const string m_description;
public:
    Command(string);
    virtual string get_desc() const;
    virtual void Execute(Server, FileVector, FileVector) = 0;
    virtual ~Command() { };
};



#endif //ADVANCEDPROGPROJECT_COMMAND_H