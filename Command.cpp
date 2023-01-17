#include "Command.h"

Command::Command(string desc) : m_description(desc) { }
string Command::get_desc() const {
    return m_description;
}