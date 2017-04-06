#include <Mocks.h>

Models::User Mocks::DatabaseMock::getUserByID(const int &id)
{
    return users.at(id);
}

std::vector<Models::User> Mocks::DatabaseMock::getAllUsers()
{
    return users.getAllUsers();
}

Models::User Mocks::DatabaseMock::getUserByCredentials(const std::string &username, const std::string &password)
{
    if (username == "jófej")
    {
        return Models::User("Jófej János", 12);
    }
    return Models::User(false);
}

Results::Database Mocks::DatabaseMock::saveUser(const Models::User &user) { 
    return Results::Database::Ok; 
    }
Results::Database Mocks::DatabaseMock::saveUser(const std::string &displayName, const std::string &username, const std::string &password) { 
    return Results::Database::Ok; 
    }
