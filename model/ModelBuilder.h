#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H
#include "Model.h"
#include "LossFn.h"

class ModelBuilder
{
    private:
        std::vector<std::shared_ptr<Layer>> layers;

        std::shared_ptr<LossFn> lossFn;

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

        std::shared_ptr<Model> build()
        {
            return std::make_shared<Model>(layers, lossFn);
        }
};

#endif