#include <string>
#include <Models.h>

Models::User::User (std::string name) : name(name){}

std::string Models::User::getName(){
    return this->name;
}