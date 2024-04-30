#ifndef LAYER_H
#define LAYER_H
#include "Node.h"
#include <iostream>
#include <memory>

class Layer
{
    private:
        // std::shared_ptr<ActivationFn> activationFn;

    public:

        std::shared_ptr<Node> weights;

        Layer(int input_size, int output_size);

};

#endif