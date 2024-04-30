#include "Node.h"
#include "Mat.h"
#include <iostream>
#include <memory>

Node::Node(std::shared_ptr<Mat> paramData)
{
    this->data = paramData;
    this->grad = std::make_shared<Mat>(*(paramData.get()), 0.0);
}


std::shared_ptr<Node> Node::operator+(Node& b)
{
    Mat resultMat = *(this->data) + *(b.data);
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat));
    
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
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat));
    
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
    std::shared_ptr<Node> out = std::make_shared<Node>(std::make_shared<Mat>(resultMat));
    
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