#include <string>
#include <Models.h>

Models::User::User(const std::string &name ,const int & id) : name(name) , id(id) {}

const std::string &Models::User::getName() const
{
    return this->name;
}

int Models::User::getID() const
{
    return this->id;
}