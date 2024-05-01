#include "Node.h"
#include "Mat.h"
#include <iostream>
#include <memory>
#include <unordered_set>

Node::Node(std::shared_ptr<Mat> paramData, std::unordered_set<std::shared_ptr<Node>> previous)
{
    this->data = paramData;
    this->grad = std::make_shared<Mat>(*(paramData.get()), 0.0);
    this->previous = previous;
}

Node::Node(std::shared_ptr<Mat> paramData) : Node(paramData, std::unordered_set<std::shared_ptr<Node>>()) 
{

}



std::shared_ptr<Node> Node::operator+(Node& b)
{

    Mat resultMat = *(this->data) + *(b.data);
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat),
        std::unordered_set<std::shared_ptr<Node>>({
            std::make_shared<Node>(b), 
            std::make_shared<Node>(*this)
        }));
    
    out->backward = [&]()
    {
        std::shared_ptr<Mat> thisGrad = std::make_shared<Mat>(*(out->grad) + *(b.grad));
        std::shared_ptr<Mat> bGrad = std::make_shared<Mat>(*(out->grad) + *(this->grad));
        b.grad = bGrad;
        this->grad = thisGrad;
    };
    return out;
}

std::shared_ptr<Node> Node::operator*(Node& b)
{
    Mat resultMat = *(this->data) * (*(b.data));
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat),
        std::unordered_set<std::shared_ptr<Node>>({
            std::make_shared<Node>(b), 
            std::make_shared<Node>(*this)
        }));
    
    out->backward = [&]()
    {
        Mat thisGrad = *(this->grad) + (*(out->grad) * (b.data->T()));
        Mat bGrad = *(b.grad) + (this->data->T() * *(out->grad));
        this->grad = std::make_shared<Mat>(thisGrad);
        b.grad = std::make_shared<Mat>(bGrad);
    };
    return out;
}

std::shared_ptr<Node> Node::operator-(Node& b)
{
    Mat resultMat = *(this->data) - *(b.data);
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat), 
        std::unordered_set<std::shared_ptr<Node>>({
            std::make_shared<Node>(b), 
            std::make_shared<Node>(*this)
        }));
    
    out->backward = [&]()
    {
        std::shared_ptr<Mat> thisGrad = std::make_shared<Mat>(*(out->grad));
        std::shared_ptr<Mat> bGrad = std::make_shared<Mat>(out->grad->mapFunction([=](int i, int j, float value) {
            return -1 * value;
        })->getPiece());
        b.grad = bGrad;
        this->grad = thisGrad;
    };
    return out;
}

std::shared_ptr<Node> Node::sum()
{
    float totalSum = 0.0;

    this->data->forEach([&totalSum](int i, int j, float value){ totalSum += value; });

    svf sumValue = {{totalSum}};

    std::shared_ptr<Node> out = std::make_shared<Node>(
        std::make_shared<Mat>(sumValue)
    );

    out->backward = [&]()
    {
        float gradientToPropagate = out->grad->getPiece()[0][0];
        svf grad = this->grad->getPiece();
        this->grad->forEach([&](int i, int j, float value){
            grad[i][j] += gradientToPropagate;
        });
    };
    return out;
}