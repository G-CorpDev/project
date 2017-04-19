#ifndef AUTHENTICATOR_HEADER
#define AUTHENTICATOR_HEADER

#include <Models.h>
#include <JWT.h>

/*! A class to handle all JSON Web Token needs.*/
class Authenticator
{
private:
  JWT::Generator tokenGenerator;
  JWT::Verifier tokenVerifier;

  std::string random_string(size_t length);

public:
  /*! \param token the JWT
  \return the user

  Verifies the JWT, then finds the User who owns it. If the JWT was invalid, the User will be **invalid** too.*/
  Models::User authenticateUser(const std::string &token);
  /*! \param user the User
  \return a JWT string

  Generates a JWT for the User.*/
  std::string generateToken(const Models::User &user);

  Authenticator();
};

#endif