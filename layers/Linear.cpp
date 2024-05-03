#include "Linear.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Mat.h"
#include "Node.h"
#include "math.h"
#include <random>


Linear::Linear(int input_size, int output_size)
{
    svf p = svf(input_size, std::vector<float>(output_size, 1));
    std::mt19937 rng(std::random_device{}());
    float k = 1 / input_size;
    float range = sqrt(k);
    std::uniform_real_distribution<double> distribution(-k, k);

    for(int rowNo = 0 ; rowNo < input_size ; rowNo++)
    {
        std::generate(p[rowNo].begin(), p[rowNo].end(), [&]() {
            return distribution(rng);
        });
    }

    this->weights = std::make_shared<Node>(
        std::make_shared<Mat>(p)
    );
}


std::shared_ptr<Node> Linear::forward(std::shared_ptr<Node> input)
{
    return input * this->weights;
}