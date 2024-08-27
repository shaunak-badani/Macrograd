#include<gtest/gtest.h>
#include "Mat.h"
#include "MatUtils.h"

struct MatUtilsParameterizedTest : public testing::TestWithParam
    <std::tuple<svf, svf, svf>>
{
    protected:
        svf a, b;
};

TEST_P(MatUtilsParameterizedTest, test_cross_correlation)
{
    svf a = std::get<0>(GetParam());
    svf b = std::get<1>(GetParam());

    std::shared_ptr<Mat> c = MatUtils::crossCorrelate(
        std::make_shared<Mat>(a), std::make_shared<Mat>(b));

    int m = a.size();
    int n = a[0].size();

    int p = b.size();
    int q = b[0].size();

    ASSERT_EQ(c->getShape().at(0), m - p + 1);
    ASSERT_EQ(c->getShape().at(1), n - q + 1);

    svf expectedCrossCorrelation = std::get<2>(GetParam());

    c->forEach([=](int i, int j, float value){
        EXPECT_FLOAT_EQ(expectedCrossCorrelation[i][j], value);
    });
}

INSTANTIATE_TEST_SUITE_P(MatUtilsTest,
    MatUtilsParameterizedTest,
    ::testing::Values(
        std::make_tuple<svf, svf, svf>(
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
            {{1, 2}, {3, 4}},
            {{37, 47}, {67, 77}}
        ),
        std::make_tuple<svf, svf, svf>(
            {{78.0, -90.0, 3.0, 4.0}, {-130.2, 8.121, 6.4, 2.5}, {4.0, 8.9, 17.2, 12.1}},
            {{1.0, 2.0}, {3.0, 4.0}},
            {{-460.116, -34.0370, 40.2000}, {-66.3580,  116.4210,  111.4000}}
        )
    ));

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}