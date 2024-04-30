#include "Node.h"
#include <gtest/gtest.h>
#include <memory>
#include <iostream>

TEST(NodeSetup, testing_node_sanity)
{
    svf tmpVector = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(tmpVector);
    std::shared_ptr<Node> node = std::make_shared<Node>(a);
    std::pair<int, int> gradShape = node->grad->getShape();
    EXPECT_EQ(gradShape.first, 2);
    EXPECT_EQ(gradShape.second, 2);
    node->grad->forEach([](int i, int j, float val){
        EXPECT_EQ(val, 0.0);
    });
}

TEST(NodeOperations, node_addition)
{
    svf vectorA = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    svf vectorB = {
        {2.0, -9.0},
        {8.1, 3.2}  
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(vectorA);
    std::shared_ptr<Node> nodeA = std::make_shared<Node>(a);

    std::shared_ptr<Mat> b = std::make_shared<Mat>(vectorB);
    std::shared_ptr<Node> nodeB = std::make_shared<Node>(b);

    std::shared_ptr<Node> c = *(nodeA.get()) - *(nodeB.get());

    svf expectedSubtractedVector = {
        {-1.0, 0.0},
        {1.7, -1.1}  
    };

    c->data->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedSubtractedVector[i][j] - value) < 1e-3);
    });

    float randomGradientValue = 57.0;
    c->grad->assignValue(randomGradientValue);

    c->backward();

    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, -1 * randomGradientValue);
    });

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
    });
}

TEST(NodeOperations, node_subtraction)
{
    svf vectorA = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    svf vectorB = {
        {2.0, -9.0},
        {8.1, 3.2}  
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(vectorA);
    std::shared_ptr<Node> nodeA = std::make_shared<Node>(a);

    std::shared_ptr<Mat> b = std::make_shared<Mat>(vectorB);
    std::shared_ptr<Node> nodeB = std::make_shared<Node>(b);

    std::shared_ptr<Node> c = *(nodeA.get()) + *(nodeB.get());

    float randomGradientValue = 57.0;
    c->grad->assignValue(randomGradientValue);

    c->backward();

    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
    });

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
    });
}


TEST(NodeOperations, node_multiplication)
{
    svf vectorA = {
        {-1.0, 2.0, -3.0, 4.0},
        {1.0, -2, 1, 3},
        {4, -3, 1, 1}
    };

    svf vectorB = {
        {4.0, 2.0},
        {-1.0, -5.0},  
        {2.0, 1.0},  
        {3.0, 1.0},  
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(vectorA);
    std::shared_ptr<Node> nodeA = std::make_shared<Node>(a);

    std::shared_ptr<Mat> b = std::make_shared<Mat>(vectorB);
    std::shared_ptr<Node> nodeB = std::make_shared<Node>(b);

    std::shared_ptr<Node> c = *nodeA * *nodeB;
    svf randomGradientValue = {
        {-1, 4},
        {2, 7},
        {6, 5}
    };

    c->grad = std::make_shared<Mat>(randomGradientValue);

    c->backward();

    svf expectedGradA = {
        {4, -19, 2, 1},
        {22, -37, 11, 13},
        {34, -31, 17, 23},  
    };

    svf expectedGradB = {
        {27,23},
        {-24,-21},
        {11,0},
        {8,42}
    };

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGradA[i][j] - value) < 1e-3);
    });

    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGradB[i][j] - value) < 1e-3);
    });
}