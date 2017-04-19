#include <Authenticator.h>

#include <sstream>
#include <ctime>

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

Authenticator::Authenticator() : tokenGenerator(Utils::random_string(20)), tokenVerifier(tokenGenerator.getSecret())
{
}