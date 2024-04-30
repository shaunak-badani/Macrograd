#include <gtest/gtest.h>
#include "LossFn.h"
#include "MeanSquaredError.h"
#include "Node.h"
#include "Mat.h"

TEST(LossFn, MeanSquaredError)
{
    svf a = {{-1.5, 2.4, 3.3, 1.9, 2.8}};

    svf b = {{7.6, -1.1, 4.2, -3.2, 10.0}};

    std::shared_ptr<Node> nodeA = std::make_shared<Node>(
        std::make_shared<Mat>(a)
    );

    std::shared_ptr<Node> nodeB = std::make_shared<Node>(
        std::make_shared<Mat>(b)
    );
    std::shared_ptr<LossFn> lossFn = std::make_shared<MeanSquaredError>();
    std::shared_ptr<Node> output = (*lossFn.get())(nodeA, nodeB);

    float expectedLoss = 173.72;
    std::pair<int, int> outputShape = output->data->getShape();

    ASSERT_EQ(outputShape.first, 1) << "Loss output should have only 1 row" << std::endl;

    ASSERT_EQ(outputShape.second, 1) << "Loss output should have only 1 column" << std::endl;
    ASSERT_TRUE(abs(expectedLoss - output->data->getPiece()[0][0]) < 1e-3);

}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
