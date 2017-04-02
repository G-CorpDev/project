#ifndef JWT_CLASSES_HEADER
#define JWT_CLASSES_HEADER

#include <jwt/jwt.h>
#include <jansson.h>
#include <string>
#include <map>

namespace JWT
{

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

class Generator : public SecretHandler
{

public:
  Generator(const std::string &secret);
  std::string generateJWT(const std::map<std::string, std::string> &payload);
};

class Verifier : public SecretHandler
{
public:
  Verifier(const std::string &secret);
  const std::map<std::string, std::string> verifyJWT(const std::string &token);
};
}

#endif