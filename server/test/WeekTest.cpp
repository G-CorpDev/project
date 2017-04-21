#include <gtest/gtest.h>

#include <Models.h>
#include <Utils.h>

namespace
{
class WeekTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};
TEST(WeekTest,toJSON){
    Models::Week week;

    Models::Day day1(Models::Day::Days::Monday);
    Models::Day day2(Models::Day::Days::Monday);
    Models::Day day3(Models::Day::Days::Tuesday);
    week.addDay(day1);
    week.addDay(day2);
    week.addDay(day3);

    std::string JSON(week.toJSON());

    ASSERT_GT(JSON.size(),0);

    Models::Week empty;
    std::string emptyJSON(empty.toJSON());

    ASSERT_GT(emptyJSON.size(),0);
}
TEST(WeekTest,AddDay){
    Models::Week week;

    Models::Day day1(Models::Day::Days::Monday);
    Models::Day day2(Models::Day::Days::Monday);
    Models::Day day3(Models::Day::Days::Tuesday);

    ASSERT_NO_THROW(week.addDay(day1));
    ASSERT_NO_THROW(week.addDay(day3));
    ASSERT_NO_THROW(week.addDay(day2));
}
}