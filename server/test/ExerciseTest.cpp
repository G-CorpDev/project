#include <gtest/gtest.h>
#include <random>
#include <limits>

#include <Models.h>
#include <Utils.h>

namespace
{
class ExerciseTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};
TEST(ExerciseTest,Constructor){
    std::string name(Utils::random_string(20));
    std::string note(Utils::random_string(20));
    std::string reps(Utils::random_string(20));
    std::string weight(Utils::random_string(20));
    bool done = true;
    Models::Exercise::Type type = Models::Exercise::Type::RepsAndWeight;

    Models::Exercise exercise(name,note,type,reps,weight,done);

    EXPECT_TRUE(exercise.isDone());
    EXPECT_EQ(exercise.getName(),name);
    EXPECT_EQ(exercise.getNote(),note);
    EXPECT_EQ(exercise.getWeight(),weight);
    EXPECT_EQ(exercise.getReps(),reps);
    EXPECT_EQ(exercise.getType(),type);
}

TEST(ExerciseTest, toJSON){
    std::string name(Utils::random_string(20));
    std::string note(Utils::random_string(20));
    std::string reps(Utils::random_string(20));
    std::string weight(Utils::random_string(20));
    bool done = true;
    Models::Exercise::Type type = Models::Exercise::Type::RepsAndWeight;

    Models::Exercise exercise(name,note,type,reps,weight,done);

    std::string JSON(exercise.toJSON());

    ASSERT_GT(JSON.size(),0);

    Models::Exercise empty("","",Models::Exercise::Type::JustDone,"","",false);

    std::string emptyJSON(empty.toJSON());

    ASSERT_GT(emptyJSON.size(),0);
}

}