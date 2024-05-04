#ifndef MODEL_H
#define MODEL_H
#include "Node.h"
#include "Layer.h"
#include <iostream>
#include <vector>
#include <memory>
#include "LossFn.h"

class Model
{
    public:
        std::vector<std::shared_ptr<Layer>> layers;
        std::shared_ptr<LossFn> lossFn;

        Model(std::vector<std::shared_ptr<Layer>> layers, std::shared_ptr<LossFn> lossFn);

        std::shared_ptr<Node> forward(std::shared_ptr<Node> input, std::shared_ptr<Node> traininglabels);

        void backward();
};

#endif
