#include <Mocks.h>

#include <iostream>

Mocks::UserMock::UserMock()
{
    this->add(std::make_pair(this->getNextID(),Models::User("Jani",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Pali",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Mari",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Sanyi",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Dani",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Gipsz Jakab",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Jacob Gibbs",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Izom Tibor",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Test Eddie",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Bob",this->getCurrentID())));
    this->add(std::make_pair(this->getNextID(),Models::User("Chrysantemum",this->getCurrentID())));
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