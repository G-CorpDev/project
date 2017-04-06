#include <Authenticator.h>
#include <algorithm>

#include <sstream>
#include <ctime>

std::string Authenticator::random_string(size_t length)
{
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

Models::User Authenticator::authenticateUser(const std::string &token)
{
    auto grants = this->tokenVerifier.verifyJWT(token);
    if (grants.size() < 3)
    {
        return Models::User(false);
    }
    else
    {
        if(std::time(0)> std::stoi(grants.at("exp")) ){return Models::User(false);}

        std::string displayName = grants.at("displayName");
        unsigned int id = std::stoi(grants.at("id"));
        return Models::User(displayName,id);
    }
    return Models::User(false);
}

std::string Authenticator::generateToken(const Models::User &user)
{
    std::map<std::string, std::string> userData;

    std::stringstream ss;
    ss << std::time(0) + 7200;
    std::string expiration(ss.str());
    userData.insert({"exp",expiration});

    userData.insert({"displayName", user.getDisplayName()});
    userData.insert({"id", std::to_string(user.getID())});

    return this->tokenGenerator.generateJWT(userData);
}

Authenticator::Authenticator() : tokenGenerator(random_string(20)), tokenVerifier(tokenGenerator.getSecret())
{
}