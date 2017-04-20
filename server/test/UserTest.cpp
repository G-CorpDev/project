#include <gtest/gtest.h>
#include <random>
#include <limits>

#include <Models.h>
#include <Utils.h>

namespace
{
class UserTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  public:
    std::random_device rd;                  // only used once to initialise (seed) engine
    std::mt19937 rng;                       // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni; // guaranteed unbiased

    UserTest() : rd(), rng(rd()), uni(0, std::numeric_limits<int>::max()) {}
};

TEST_F(UserTest, ConstructorAndGetters)
{
    std::string nickname(Utils::random_string(20));
    auto random_integer = uni(rng);
    Models::User user(nickname, random_integer);
    EXPECT_EQ(user.getDisplayName(),nickname);
    EXPECT_EQ(user.getID(),random_integer);
}

TEST_F(UserTest, VerifiedTests){
    std::string nickname(Utils::random_string(20));
    auto random_integer = uni(rng);
    Models::User user(nickname, random_integer);
    Models::User unauthenticatedUser(false);
    EXPECT_TRUE(user.isValid());
    EXPECT_FALSE(unauthenticatedUser.isValid());
}
}