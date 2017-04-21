#include <gtest/gtest.h>
#include <random>
#include <limits>

#include <Models.h>
#include <Utils.h>

namespace
{
class WorkoutTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};
TEST(WorkoutTest,Constructor){
    Models::Workout workout("Name","Desc.",Models::Workout::TimeOfDay::Morning,true,false);
    auto time = workout.getTime();

    ASSERT_EQ(time,Models::Workout::TimeOfDay::Morning);
}
TEST(WorkoutTest,AddExercise){
    Models::Workout workout("Name","Desc.",Models::Workout::TimeOfDay::Morning,true,false);

    std::string name(Utils::random_string(20));
    std::string note(Utils::random_string(20));
    std::string reps(Utils::random_string(20));
    std::string weight(Utils::random_string(20));
    bool done = true;
    Models::Exercise::Type type = Models::Exercise::Type::RepsAndWeight;

    Models::Exercise exercise(name,note,type,reps,weight,done);

    ASSERT_NO_THROW(workout.addExercise(exercise));
}
TEST(WorkoutTest,toJSON){
    Models::Workout workout("Name","Desc.",Models::Workout::TimeOfDay::Morning,true,false);
    Models::Exercise ex("","",Models::Exercise::Type::RepsOnly,"","",true);

    workout.addExercise(ex);
    std::string JSON(workout.toJSON());

    ASSERT_GT(JSON.size(),0);

    Models::Workout empty("","",Models::Workout::TimeOfDay::Morning,false,false);

    std::string emptyJSON(empty.toJSON());

    ASSERT_GT(emptyJSON.size(),0);
}
TEST(WorkoutTest,TimeFromString){
    auto morning = Models::Workout::timeFromString("morning");
    auto midday = Models::Workout::timeFromString("Midday");
    auto evening = Models::Workout::timeFromString("evening");
    auto invalid = Models::Workout::timeFromString("NEVER");

    ASSERT_EQ(morning,Models::Workout::TimeOfDay::Morning);
    ASSERT_EQ(midday,Models::Workout::TimeOfDay::Day);
    ASSERT_EQ(evening,Models::Workout::TimeOfDay::Evening);
    ASSERT_EQ(invalid,Models::Workout::TimeOfDay::Invalid);
}
}