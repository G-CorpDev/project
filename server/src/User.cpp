#include <string>
#include <Models.h>

Models::User::User(
    const std::string &displayName,
    const int &age,
    const float &weight,
    const float &height,
    const int &sex,
    const unsigned int &id)
    : id(id), displayName(displayName), age(age), weight(weight), height(height), sex(sex), verified(true) {}

Models::User::User(bool verified)
    : id(0), displayName("Unverified user!"), age(0), weight(0), height(0), sex(-1), verified(verified) {}

const std::string &Models::User::getDisplayName() const
{
    return this->displayName;
}

unsigned int Models::User::getID() const
{
    return this->id;
}

int Models::User::getAge() const
{
    return this->age;
}

float Models::User::getHeight() const
{
    return this->height;
}

float Models::User::getWeight() const
{
    return this->weight;
}

int Models::User::getSex() const
{
    return this->sex;
}