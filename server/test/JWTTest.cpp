#include <gtest/gtest.h>
#include <random>
#include <limits>

#include <map>

#include <Models.h>
#include <Utils.h>
#include <JWT.h>

namespace
{
class JWTTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(JWTTest, SecretHandler)
{
    std::string secret(Utils::random_string(20));
    JWT::SecretHandler handler(secret);
    EXPECT_EQ(secret, handler.getSecret());
}

TEST_F(JWTTest, JWTGenerationAndVerification)
{
    std::string secret(Utils::random_string(20));
    JWT::Generator gen(secret);
    JWT::Verifier ver(secret);

    std::map<std::string, std::string> payload;
    payload.insert({"key", "value"});
    payload.insert({"key2", "value2"});
    payload.insert({"key3", "value3"});

    std::string token(gen.generateJWT(payload));

    auto decoded(ver.verifyJWT(token));

    std::string value(decoded.at("key"));
    std::string value2(decoded.at("key2"));
    std::string value3(decoded.at("key3"));

    EXPECT_EQ(value, "value");
    EXPECT_EQ(value2, "value2");
    EXPECT_EQ(value3, "value3");
}

TEST_F(JWTTest, VerifyInvalidToken)
{
    std::string secret(Utils::random_string(20));
    JWT::Verifier ver(secret);

    std::string token("{this is not a valid JSON]");

    auto decoded(ver.verifyJWT(token));

    EXPECT_EQ(decoded.size(), 0);
}
}