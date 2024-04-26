#include "Node.h"
#include <gtest/gtest.h>


TEST(NodeSetup, testing_node_sanity)
{
    svf tmpVector = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    Mat* a = new Mat(tmpVector);
    Node* node = new Node(a);
    std::pair<int, int> gradShape = node->grad->getShape();
    EXPECT_EQ(gradShape.first, 2);
    EXPECT_EQ(gradShape.second, 2);
    node->grad->mapFunction([](int i, int j, float val){
        EXPECT_EQ(val, 0.0);
        return 0.0;
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

    Mat* a = new Mat(vectorA);
    Node* nodeA = new Node(a);

    Mat* b = new Mat(vectorB);
    Node* nodeB = new Node(b);

    Node c = *nodeA + *nodeB;
    float randomGradientValue = 57.0;
    c.grad->assignValue(randomGradientValue);

    c.backward();

    nodeB->grad->mapFunction([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
        return 1.0;
    });

    nodeA->grad->mapFunction([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
        return 1.0;
    });
}