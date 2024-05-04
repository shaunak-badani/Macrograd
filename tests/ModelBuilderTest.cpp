#include <gtest/gtest.h>
#include "Linear.h"
#include "MeanSquaredError.h"
#include "Model.h"
#include "Node.h"
#include "ModelBuilder.h"

struct ModelBuilderTest : testing::Test
{
    std::vector<std::shared_ptr<Layer>> layers;
    std::shared_ptr<LossFn> lossFn;
    std::shared_ptr<ModelBuilder> modelBuilder;

    // test input
    svf test_vec;
    std::shared_ptr<Node> test_node;

    // test output
    svf test_labels_vec;
    std::shared_ptr<Node> test_labels;

    void SetUp() override
    {
        layers.push_back(std::make_shared<Linear>(10, 1));
        lossFn = std::make_shared<MeanSquaredError>();

        test_vec = svf(5, std::vector<float>(10, 9.1));
        test_node = std::make_shared<Node>(
                std::make_shared<Mat>(test_vec)
            );

        test_labels_vec = svf(5, std::vector<float>(1, 1));
        test_labels = std::make_shared<Node>(
                std::make_shared<Mat>(test_labels_vec)
            );
        modelBuilder = std::make_shared<ModelBuilder>();
    }
    
    void TearDown() override
    {

    }
};


TEST_F(ModelBuilderTest, test_build_model_exceptions)
{
    // without any parameters
    EXPECT_THROW(
        modelBuilder->build(),
        std::runtime_error
    );

    // with only loss fn, will not throw error while creation.
    modelBuilder->setLossFn(lossFn);
    EXPECT_NO_THROW(
        modelBuilder->build()
    );

    // with standard layer and loss fn, should not throw any error while creation
    modelBuilder->addLayer(layers.front());
    EXPECT_NO_THROW(
        modelBuilder->build()
    );

    // with null layers
    std::shared_ptr<Layer> nullLayer;
    modelBuilder->addLayer(nullLayer);
    EXPECT_THROW(
        modelBuilder->build(),
        std::runtime_error
    );
}