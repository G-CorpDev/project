#include <Mocks.h>

Mocks::UserMock::UserMock()
{
    this->getNextID();
    this->add(std::make_pair(std::make_pair("jani", "jelszo"), Models::User("Jani", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("pali", "jelszo"), Models::User("Pali", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("mari", "jelszo"), Models::User("Mari", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("sanyi", "jelszo"), Models::User("Sanyi", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("dani", "jelszo"), Models::User("Dani", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("gipsz", "jelszo"), Models::User("Gipsz Jakab", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("gibbs", "jelszo"), Models::User("Jacob Gibbs", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("izom", "jelszo"), Models::User("Izom Tibor", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("test", "jelszo"), Models::User("Test Eddie", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("bob", "jelszo"), Models::User("Bob", (this->getNextID()))));
    this->add(std::make_pair(std::make_pair("chrys", "jelszo"), Models::User("Chrysantemum", (this->getNextID()))));
}

bool Mocks::UserMock::add(const std::pair<std::pair<std::string, std::string>, Models::User> &user)
{
    try
    {
        users.insert(user);
    }
    catch (std::exception e)
    {
        return false;
    }
    return true;
}

Models::User Mocks::UserMock::getUserByID(const int &id)
{
    for(auto & user : users){
        if(user.second.getID()==id){
            return user.second;
        }
    }
    return Models::User(false);
}

Models::User Mocks::UserMock::getUserByCredentials(const std::pair<std::string, std::string> &credentials)
{
    try
    {
        return users.at(credentials);
    }
    catch (std::exception e)
    {
    }
    return Models::User(false);
}

std::vector<Models::User> Mocks::UserMock::getAllUsers()
{
    std::vector<Models::User> vec;
    for (auto it = users.cbegin(); it != users.cend(); ++it)
    {
        vec.push_back((*it).second);
    }
    return vec;
}

int Mocks::UserMock::getNextID()
{
    return ++(this->idcounter);
}