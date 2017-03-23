#include <Mocks.h>

Models::User Mocks::DatabaseMock::getUserByID(const int & id){
    return users.at(id);
}

std::vector<Models::User> Mocks::DatabaseMock::getAllUsers(){
    return users.getAllUsers();
}
