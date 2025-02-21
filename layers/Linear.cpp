#include "Linear.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Mat.h"
#include "Node.h"
#include "math.h"
#include "Broadcast.h"
#include <random>


Linear::Linear(int input_size, int output_size)
{
    svf p = svf(input_size, std::vector<float>(output_size, 1));
    std::mt19937 rng(std::random_device{}());
    float k = 1 / (input_size * 1.0f);
    std::cout << "k : " << k << std::endl;
    float range = sqrt(k);
    std::uniform_real_distribution<double> distribution(-k, k);

    for(int rowNo = 0 ; rowNo < input_size ; rowNo++)
    {
        std::generate(p[rowNo].begin(), p[rowNo].end(), [&]() {
            return distribution(rng);
        });
    }

    std::cout << "Random matrix : " << std::endl;
    for(int i = 0 ; i < p.size() ; i++)
    {
        for(int j = 0 ; j < p[0].size() ; j++)
        {
            std::cout << p[i][j] << " ";
        }
        std::cout << std::endl;
    }

    this->weights = std::make_shared<Node>(
        std::make_shared<Mat>(p)
    );

    // std::cout << "Weights during initialization " << std::endl;
    // std::cout << *(this->weights->data.get()) << std::endl;

    svf bias = svf(1, std::vector<float>(output_size, 1));

    std::generate(bias[0].begin(), bias[0].end(), [&]() {
        return distribution(rng);
    });

    this->biases = std::make_shared<Node>(
        std::make_shared<Mat>(bias)
    );
}


std::shared_ptr<Node> Linear::forward(std::shared_ptr<Node> input)
{
    std::shared_ptr<Node> intermediate = input * this->weights;
    std::cout << "This weight data: " << *(this->weights->data.get()) << std::endl;
    std::cout << "This weight T data: " << this->weights->data->T() << std::endl;
    return std::shared_ptr<Broadcast::Add>()->calculate(intermediate, biases);
}

std::vector<std::shared_ptr<Node>> Linear::getParameters()
{
    return {this->weights, this->biases};
}