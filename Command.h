
#ifndef ADVANCEDPROGPROJECT_COMMAND_H
#define ADVANCEDPROGPROJECT_COMMAND_H
#include <stdio.h>
#include <string>
using namespace std;
class Command {
private:
    string m_description;
public:
    virtual void Execute() const  = 0;
    virtual ~Command(){
    };
    string get_desc();

};



#endif //ADVANCEDPROGPROJECT_COMMAND_H
