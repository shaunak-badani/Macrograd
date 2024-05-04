#include "Model.h"

Model::Model(std::vector<std::shared_ptr<Layer>> layers, std::shared_ptr<LossFn> lossFn)
{
    for(std::shared_ptr<Layer> layer : layers)
    {
        if(!layer)
            throw std::runtime_error("Can't initialize a model with a null layer!");
    }
    this->layers = layers;
    if(!lossFn)
        throw std::runtime_error("Can't initialize a model without a loss function!");

    this->lossFn = lossFn;
}

std::shared_ptr<Node> Model::forward(std::shared_ptr<Node> input, std::shared_ptr<Node> traininglabels)
{
    std::shared_ptr<Node> x = input;
    for(std::shared_ptr<Layer> layer : layers)
    {
        x = layer->forward(x);
    }
    std::pair<int, int> outputShape = x->data->getShape();
    std::pair<int, int> labelsShape = traininglabels->data->getShape();
    if(outputShape.second != labelsShape.second)
    {
        throw std::runtime_error("Label dimension doesn't match layer output dimension!");
    }
    if(outputShape.first != labelsShape.first)
    {
        throw std::runtime_error("Number of elements in input and labels does not match!");
    }
    std::shared_ptr<Node> loss = (this->lossFn.get())->operator()(x, traininglabels);
    return loss;
}