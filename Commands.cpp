#include "Commands.h"

first_command::first_command() : Command("upload an unclassified csv data file"){}
void  first_command :: Execute(){}

second_command::second_command() : Command("algorithm settings"){}
void  second_command :: Execute(){}

third_command::third_command() : Command("classify data"){}
void  third_command :: Execute(){}

fourth_command::fourth_command() : Command("display result"){}
void  fourth_command :: Execute(){}

fifth_command::fifth_command() : Command("download results"){}
void  fifth_command :: Execute(){}
