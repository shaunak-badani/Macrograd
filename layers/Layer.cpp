#include "Layer.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Mat.h"


Layer::Layer(int input_size, int output_size)
{
    svf p = svf(input_size, std::vector<float>(output_size, 1));
    this->weights = std::make_shared<Node>(
        std::make_shared<Mat>(p)
    );
}