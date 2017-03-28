#include <Authenticator.h>
#include <algorithm>

#include <iostream>

std::string Authenticator::random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

Models::User Authenticator::authenticateUser(const std::string & token){
    auto grants = this->tokenVerifier.verifyJWT(token);
    for(auto grant : grants){
        std::cout<<grant.first<<":"<<grant.second<<std::endl;
    }
}

std::string Authenticator::generateToken(const Models::User & user){
    std::map<std::string,std::string> userData;
    userData.insert({"displayName",user.getDisplayName()});
    userData.insert({"id",std::to_string(user.getID())});
    return this->tokenGenerator.generateJWT(userData);
}


Authenticator::Authenticator() : tokenGenerator(random_string(20)), tokenVerifier(tokenGenerator.getSecret()){
}