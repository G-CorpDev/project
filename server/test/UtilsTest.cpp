#include <gtest/gtest.h>

#include <Utils.h>

namespace
{
TEST(UtilsTest, RandomStringTest)
{
    std::string longstring(Utils::random_string(20));
    std::string shortstring(Utils::random_string(5));
    std::string empty(Utils::random_string(0));
    EXPECT_EQ(longstring.size(), 20);
    EXPECT_EQ(shortstring.size(), 5);
    EXPECT_EQ(empty.size(), 0);
}

TEST(UtilsTest, MakeSimpleJSON)
{
    std::map<std::string,std::string> data;
    data.insert({"key","value"});
    data.insert({"key2","value2"});
    data.insert({"key3","value3"});
    data.insert({"key4","value4"});

    std::string JSON(Utils::makeSimpleJSON(data));

    EXPECT_GT(JSON.size(),0);
}
TEST(UtilsTest, MakeSimpleJSONEmpty)
{
    std::map<std::string,std::string> data;

    std::string JSON(Utils::makeSimpleJSON(data));

    EXPECT_GT(JSON.size(),0);
}
TEST(UtilsTest, DecodeSimpleJSON)
{
    auto data = Utils::decodeSimpleJSON("{\"key\":\"value\",\"key2\":\"value2\",\"boolValue\":false,\"intValue\":12}");
    ASSERT_EQ(data.size(),4);
    EXPECT_EQ(data.at("key"),"value");
    EXPECT_EQ(data.at("key2"),"value2");
    EXPECT_EQ(data.at("boolValue"),"false");
    EXPECT_EQ(data.at("intValue"),"12");
}

TEST(UtilsTest, DecodeSimpleJSONEmpty)
{
    auto data = Utils::decodeSimpleJSON("");
    EXPECT_EQ(data.size(),0);
}

TEST(UtilsTest, DecodeSimpleJSONMalformed)
{
    auto data = Utils::decodeSimpleJSON("This isn't even a JSON.");
    EXPECT_EQ(data.size(),0);
}
}