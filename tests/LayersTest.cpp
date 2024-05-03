#include <gtest/gtest.h>
#include "Layer.h"

TEST(LayersTest, test_layers_initialized_properly)
{
    std::shared_ptr<Layer> layer = std::make_shared<Layer>(10, 3);

    std::pair<int, int> shape = layer->weights->data->getShape();
    EXPECT_EQ(shape.first, 10);
    EXPECT_EQ(shape.second, 3);

    layer->weights->data->forEach([=](int i, int j, float value){
        EXPECT_LE(value, 1.0);
        EXPECT_GE(value, -1.0);
    });
}


int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}