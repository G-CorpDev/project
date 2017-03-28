#include <Mocks.h>

Mocks::UserMock::UserMock()
{
    this->add(std::make_pair(this->getNextID(),Models::User("Jani",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Pali",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Mari",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Sanyi",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Dani",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Gipsz Jakab",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Jacob Gibbs",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Izom Tibor",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Test Eddie",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Bob",0,0,0,0,(this->getCurrentID()))));
    this->add(std::make_pair(this->getNextID(),Models::User("Chrysantemum",0,0,0,0,(this->getCurrentID()))));
}

bool Mocks::UserMock::add(const std::pair<int, Models::User> & user){
    users.insert(user);
}

Models::User Mocks::UserMock::at(const int & id){
    return users.at(id);
}

std::vector<Models::User> Mocks::UserMock::getAllUsers(){
    std::vector<Models::User> vec;
    for(auto it = users.cbegin();it!=users.cend();++it){
        vec.push_back((*it).second);
    }
    return vec;
}

int Mocks::UserMock::getNextID(){
    return ++(this->idcounter);
}

int Mocks::UserMock::getCurrentID(){
    return (this->idcounter);
}