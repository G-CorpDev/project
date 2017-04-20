#include <gtest/gtest.h>
#include <random>
#include <limits>

#include <Models.h>
#include <Utils.h>
#include <JWT.h>
#include <Authenticator.h>

namespace
{
class AuthenticatorTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  public:
    std::random_device rd;                  // only used once to initialise (seed) engine
    std::mt19937 rng;                       // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

    AuthenticatorTest() : rd(), rng(rd()), uni(0, std::numeric_limits<int>::max()) {}
};
TEST_F(AuthenticatorTest, GenerateAndVerify)
{
    Authenticator auth;

    std::string nickname(Utils::random_string(20));
    auto random_integer = uni(rng);
    Models::User user(nickname, random_integer);

    std::string token(auth.generateToken(user));

    Models::User decoded(auth.authenticateUser(token));

    EXPECT_EQ(decoded.getID(), random_integer);
    EXPECT_EQ(decoded.getDisplayName(), nickname);
}

TEST_F(AuthenticatorTest, InvalidToken)
{
    Authenticator auth;

    std::string token("This is an invalid token!");

    Models::User decoded(auth.authenticateUser(token));

    EXPECT_FALSE(decoded.isValid());
}
}