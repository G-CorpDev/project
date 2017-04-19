#ifndef JWT_CLASSES_HEADER
#define JWT_CLASSES_HEADER

#include <jwt/jwt.h>
#include <jansson.h>
#include <string>
#include <map>

/*! Namespace containing classes working with JSON Web Tokens.*/
namespace JWT
{
/*! A class for storing a secret key securely.*/
class SecretHandler
{
  friend class Generator;
  friend class Verifier;

private:
  const std::string secret;
  unsigned char *secret_raw;

public:
  SecretHandler(const std::string &secret);
  ~SecretHandler();

  const std::string &getSecret() const;
};

/*! Generates JWTs*/
class Generator : public SecretHandler
{

public:
  Generator(const std::string &secret);

  /*! \param payload the grants, that is key-value pairs to be encoded into the JWT.
  \returns a signed JWT string

  Constructs, encodes and signs a JWT made from the payload.*/ 
  std::string generateJWT(const std::map<std::string, std::string> &payload);
};

/*! Verify JWTs*/
class Verifier : public SecretHandler
{
public:
  Verifier(const std::string &secret);
  /*!\param token the encoded and signed JWT
  \return the grants decoded, that is key-value pairs.

  Verifies the signature of the JWT, then if valid, decodes the grants contained within. If the JWT was **invalid**, returns an empty map.*/
  const std::map<std::string, std::string> verifyJWT(const std::string &token);
};
}

#endif