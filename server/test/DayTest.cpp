#include <gtest/gtest.h>
#include <random>
#include <limits>

#include <Models.h>
#include <Utils.h>

namespace
{
class DayTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};
TEST(DayTest,AddWorkout){
    Models::Workout morning("Name","Desc.",Models::Workout::TimeOfDay::Morning,true,false);
    Models::Workout midday("Name","Desc.",Models::Workout::TimeOfDay::Day,true,false);
    Models::Workout evening("Name","Desc.",Models::Workout::TimeOfDay::Evening,true,false);

    Models::Day day(Models::Day::Days::Monday);

    ASSERT_NO_THROW(day.addWorkout(morning));
    ASSERT_NO_THROW(day.addWorkout(midday));
    ASSERT_NO_THROW(day.addWorkout(evening));
    ASSERT_NO_THROW(day.addWorkout(morning));
}
TEST(DayTest,toJSON){
    Models::Day day(Models::Day::Days::Monday);

    std::string JSON(day.toJSON());

    ASSERT_GT(JSON.size(),0);
}
TEST(DayTest,DayAsString){
    std::string string(Models::Day::dayAsString(Models::Day::Days::Monday));
    EXPECT_EQ(string,"Monday");
}
TEST(DayTest,DayFromString){
    auto day1 = Models::Day::fromString("Monday");
    auto day2 = Models::Day::fromString("monday");
    auto invalid = Models::Day::fromString("Not even a day!");

    ASSERT_EQ(day1,Models::Day::Days::Monday);
    ASSERT_EQ(day2,Models::Day::Days::Monday);
    ASSERT_EQ(invalid,Models::Day::Days::Invalid);
}
}