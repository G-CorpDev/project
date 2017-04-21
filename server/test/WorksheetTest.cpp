#include <gtest/gtest.h>

#include <Models.h>
#include <Utils.h>

namespace
{
class WorksheetTest : public ::testing::Test
{
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};
TEST(WorksheetTest,toJSON){
    Models::Worksheet worksheet("Worksheet","This is a worksheet.","37 eons","Strodavenium");

    Models::Week week1;
    Models::Week week2;
    Models::Week week3;
    worksheet.addWeek(week1);
    worksheet.addWeek(week2);
    worksheet.addWeek(week3);

    std::string JSON(worksheet.toJSON());

    ASSERT_GT(JSON.size(),0);

    Models::Worksheet empty("","","","");
    std::string emptyJSON(empty.toJSON());

    ASSERT_GT(emptyJSON.size(),0);
}
TEST(WorksheetTest,addWeek){
    Models::Worksheet worksheet("Worksheet","This is a worksheet.","37 eons","Strodavenium");

    Models::Week week1;
    Models::Week week2;
    Models::Week week3;
    
    ASSERT_NO_THROW(worksheet.addWeek(week1));
    ASSERT_NO_THROW(worksheet.addWeek(week3));
    ASSERT_NO_THROW(worksheet.addWeek(week2));
}
}