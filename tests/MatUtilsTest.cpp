#include<gtest/gtest.h>
#include "Mat.h"
#include "MatUtils.h"

struct MatUtilsTest : public testing::Test
{
    svf a, b;

    void SetUp() override
    {
        a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        b = {{1, 2}, {3, 4}};
    }
};

TEST_F(MatUtilsTest, test_cross_correlation)
{
    std::shared_ptr<Mat> c = MatUtils::crossCorrelate(
        std::make_shared<Mat>(a), std::make_shared<Mat>(b));

    ASSERT_EQ(c->getShape().at(0), 2);
    ASSERT_EQ(c->getShape().at(1), 2);

    svf expectedCrossCorrelation = {{37, 47}, {67, 77}};

    c->forEach([=](int i, int j, float value){
        EXPECT_FLOAT_EQ(expectedCrossCorrelation[i][j], value);
    });
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}