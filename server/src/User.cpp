#include <string>
#include <Models.h>

Models::User::User(
    const std::string &displayName,
    const unsigned int &id)
    : id(id), displayName(displayName), verified(true) {}

Models::User::User(bool verified)
    : id(0), displayName("Unverified user!"), verified(verified) {}

const std::string &Models::User::getDisplayName() const
{
    return this->displayName;
}

unsigned int Models::User::getID() const
{
    return this->id;
}

bool Models::User::isValid() const
{
    return this->verified;
}