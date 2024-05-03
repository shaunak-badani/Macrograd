#ifndef LAYER_H
#define LAYER_H

class Layer
{
    public:
        virtual std::shared_ptr<Node> forward(std::shared_ptr<Node> input) = 0;
};

#endif