#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H
#include "Model.h"
#include "LossFn.h"
#include "LearningRate.h"

class ModelBuilder
{
    private:
        std::vector<std::shared_ptr<Layer>> layers;

        std::shared_ptr<LossFn> lossFn;

        std::shared_ptr<LearningRate> learningRate;

    public:
        ModelBuilder& addLayer(std::shared_ptr<Layer> layer)
        {
            this->layers.push_back(layer);
            return *this;
        }

        ModelBuilder& setLossFn(std::shared_ptr<LossFn> lossFn)
        {
            this->lossFn = lossFn;
            return *this;
        }

        ModelBuilder& setLearningRate(std::shared_ptr<LearningRate> lr)
        {
            this->learningRate = lr;
            return *this;
        }

        std::shared_ptr<Model> build()
        {
            return std::make_shared<Model>(layers, lossFn, learningRate);
        }
};

#endif