#include <string>
#include <Models.h>

Models::User::User(
    const std::string &displayName,
    const int &age,
    const float &weight,
    const float &height,
    const int &sex,
    const unsigned int &id)
    : id(id), displayName(displayName), age(age), weight(weight) , height(height) , sex(sex) {}

const std::string &Models::User::getDisplayName() const
{
    return this->displayName;
}

unsigned int Models::User::getID() const
{
    return this->id;
}