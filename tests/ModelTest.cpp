#include <gtest/gtest.h>
#include "Model.h"
#include "Linear.h"
#include "MeanSquaredError.h"
#include "StaticLR.h"
#include <cmath>


struct ModelTest : testing::Test
{
    std::vector<std::shared_ptr<Layer>> layers;
    std::shared_ptr<LossFn> lossFn;

    // test input
    svf test_vec;
    std::shared_ptr<Node> test_node;

    // test output
    svf test_labels_vec;
    std::shared_ptr<Node> test_labels;

    std::shared_ptr<LearningRate> staticLR;
    int batchSize = 9;

    void SetUp() override
    {
        layers.push_back(std::make_shared<Linear>(10, 1));
        lossFn = std::make_shared<MeanSquaredError>();

        test_vec = svf(batchSize, std::vector<float>(10, 9.1));
        test_node = std::make_shared<Node>(
                std::make_shared<Mat>(test_vec)
            );

        test_labels_vec = svf(batchSize, std::vector<float>(1, 1));
        test_labels = std::make_shared<Node>(
                std::make_shared<Mat>(test_labels_vec)
            );
        staticLR = std::make_shared<StaticLR>(0.2);
    }
    
    void TearDown() override
    {

    }
};

TEST_F(ModelTest, test_model_with_null_layer)
{
    std::shared_ptr<Layer> nullLayer;
    std::vector<std::shared_ptr<Layer>> nullLayers = {nullLayer};
    EXPECT_THROW(
        std::shared_ptr<Model> p = std::make_shared<Model>(nullLayers, lossFn, staticLR),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_null_loss)
{
    std::shared_ptr<LossFn> nullLossFn;
    EXPECT_THROW(
        std::shared_ptr<Model> p = std::make_shared<Model>(layers, nullLossFn, staticLR),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_null_learning_rate)
{
    std::shared_ptr<LearningRate> nullLearningRate;
    EXPECT_THROW(
        std::shared_ptr<Model> p = std::make_shared<Model>(layers, lossFn, nullLearningRate),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_incorrect_dimensions)
{
    std::shared_ptr<Model> model;
    layers.push_back(std::make_shared<Linear>(1, 3));
    model = std::make_shared<Model>(layers, lossFn, staticLR);
    std::shared_ptr<Node> loss;
    EXPECT_THROW(
        loss = model->forward(test_node, test_labels),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_incorrect_input_size_and_labels)
{
    std::shared_ptr<Model> model;
    layers.push_back(std::make_shared<Linear>(1, 3));
    model = std::make_shared<Model>(layers, lossFn, staticLR);

    svf incorrectInput = svf(6, std::vector<float>(10, 9.1));
    std::shared_ptr<Node> incorrectInputNode = std::make_shared<Node>(
        std::make_shared<Mat>(incorrectInput)
    );
    std::shared_ptr<Node> loss;
    EXPECT_THROW(
        loss = model->forward(incorrectInputNode, test_labels),
        std::runtime_error
    );

    svf incorrectLabels = svf(6, std::vector<float>(1, 1.1));
    std::shared_ptr<Node> incorrectLabelsNode = std::make_shared<Node>(
        std::make_shared<Mat>(incorrectLabels)
    );
    EXPECT_THROW(
        loss = model->forward(test_node, incorrectLabelsNode),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_works_correctly)
{
    std::shared_ptr<Model> model;
    EXPECT_NO_THROW(
        model = std::make_shared<Model>(layers, lossFn, staticLR);
    );

    std::shared_ptr<Node> loss;
    EXPECT_NO_THROW(
        loss = model->forward(test_node, test_labels)
    );

    // Asserting loss is a scalar
    std::vector<int> lossShape = loss->data->getShape();
    EXPECT_EQ(lossShape.at(0), 1);
    EXPECT_EQ(lossShape.at(1), 1);

    std::shared_ptr<LayerUtils> utils = std::make_shared<LayerUtils>();
    utils->backward(loss);

    for(std::shared_ptr<Node> param : model->parameters())
    {
        float gradientNorm = 0;
        std::shared_ptr<Mat> grad = param->grad;
        std::vector<int> shape = grad->getShape();
        int m = shape[0];
        int n = shape[1];

        for(int i = 0 ; i < m ; i++)
        {
            for(int j = 0 ; j < n ; j++)
            {
                gradientNorm += pow(grad->at(i, j), 2);
            }
        }

        EXPECT_GT(abs(gradientNorm), 0.0);
    }
}

TEST_F(ModelTest, test_gradients_populated_correctly)
{
    std::shared_ptr<Model> model;

    std::vector<std::shared_ptr<Layer>> multiLayers;
    multiLayers.push_back(std::make_shared<Linear>(10, 15));
    multiLayers.push_back(std::make_shared<Linear>(15, 1));

    // multiLayers.push_back(std::make_shared<Linear>(10, 1));


    EXPECT_NO_THROW(
        model = std::make_shared<Model>(multiLayers, lossFn, staticLR);
    );

    std::shared_ptr<Node> loss;
    EXPECT_NO_THROW(
        loss = model->forward(test_node, test_labels)
    );
    std::cout << "Loss value: " << loss->data->at(0, 0) << std::endl;

    // Asserting loss is a scalar
    std::vector<int> lossShape = loss->data->getShape();
    // EXPECT_EQ(lossShape.at(0), 1);
    // EXPECT_EQ(lossShape.at(1), 1);

    std::shared_ptr<LayerUtils> utils = std::make_shared<LayerUtils>();
    utils->backward(loss);

    int i = 0;

    std::cout << "Model parameters:" << std::endl;

    for(std::shared_ptr<Node> param : model->parameters())
    {
        float gradientNorm = 0;
        std::shared_ptr<Mat> grad = param->grad;
        std::vector<int> shape = grad->getShape();
        int m = shape[0];
        int n = shape[1];
        std::cout << param.get() << "  :: ";

        for(int i = 0 ; i < m ; i++)
        {
            for(int j = 0 ; j < n ; j++)
            {
                gradientNorm += pow(grad->at(i, j), 2);
            }
        }

        EXPECT_GT(abs(gradientNorm), 0.0);
    }
    std::cout << std::endl;
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}