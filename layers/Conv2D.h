#ifndef CONV_2D_H
#define CONV_2D_H
#include "Node4D.h"
#include "Node.h"


class Conv2D
{
    private:
        std::shared_ptr<Node4D> kernel;
        std::shared_ptr<Node> bias;
    public:
        Conv2D(int out_channels, int in_channels, int kernel_size);

};

#endif