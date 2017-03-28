#ifndef AUTHENTICATOR_HEADER
#define AUTHENTICATOR_HEADER

#include <Models.h>
#include <JWT.h>

class Authenticator
{
  private:
    JWT::Generator tokenGenerator;
    JWT::Verifier tokenVerifier;

    std::string random_string( size_t length );

  public:
    Models::User authenticateUser(const std::string &token);
    std::string generateToken(const Models::User & user);

    Authenticator();
};

#endif