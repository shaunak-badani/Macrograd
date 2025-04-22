#include "Conv2D.h"
#include "Node4D.h"
#include <random>
#include <vector>


Conv2D::Conv2D(int out_channels, int in_channels, int kernel_size)
{
    float k = 1 / (in_channels * kernel_size * kernel_size * 1.0f);
    std::vector<std::vector<svf>> kernelVector;
    std::mt19937 rng(std::random_device{}());
    float range = sqrt(k);
    std::uniform_real_distribution<double> distribution(-range, range);

    for(int i = 0 ; i < out_channels ; i++)
    {
        std::vector<svf> currentVector;
        for(int j = 0 ; j < in_channels ; j++)
        {
            svf p = svf(kernel_size, std::vector<float>(kernel_size, 1));
            for(int rowNo = 0 ; rowNo < kernel_size ; rowNo++)
            {
                std::generate(p[rowNo].begin(), p[rowNo].end(), [&]() {
                    return distribution(rng);
                });
            }
            currentVector.push_back(p);
        }
        kernelVector.push_back(currentVector);
    }
    this->kernel = std::make_shared<Node4D>(
        std::make_shared<Vec4D>(kernelVector)
    );

    svf bias = svf(1, std::vector<float>(out_channels, 1));
    std::generate(bias[0].begin(), bias[0].end(), [&]() {
        return distribution(rng);
    });

    this->bias = std::make_shared<Node>(
        std::make_shared<Mat>(bias)
    );
}