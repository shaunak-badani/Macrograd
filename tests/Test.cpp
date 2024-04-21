#include <iostream>
#include "IOUtils.h"
#include <gtest/gtest.h>

TEST(Ioutils, split_string)
{
    std::string stringToSeparate = "Today,was,a,good,day";

    std::vector<std::string> separatedString = IOUtils::split_comma_separated_string(stringToSeparate);

    std::vector<std::string> expectedVector = {"Today", "was", "a", "good", "day"};

    ASSERT_EQ(separatedString.size(), expectedVector.size()) << "Expected size does not match actual size";

    int actualLength = separatedString.size();
    for(int index = 0 ; index < actualLength ; index++)
    {
        EXPECT_STREQ(expectedVector[index].c_str(), separatedString[index].c_str());
    }
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}