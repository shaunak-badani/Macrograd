#include "Node.h"
#include "Mat.h"
#include <iostream>
#include <memory>

Node::Node(std::shared_ptr<Mat> paramData)
{
    this->data = paramData;
    this->grad = std::make_shared<Mat>(*(paramData.get()), 0.0);
}


Node Node::operator+(Node& b)
{
    Mat resultMat = *(this->data) + *(b.data);
    Node out(std::make_shared<Mat>(resultMat));
    
    out.backward = [&]()
    {
        std::shared_ptr<Mat> thisGrad = std::make_shared<Mat>(*(out.grad) + *(b.grad));
        std::shared_ptr<Mat> bGrad = std::make_shared<Mat>(*(out.grad) + *(this->grad));
        b.grad = bGrad;
        this->grad = thisGrad;
    };
    return out;
}

Node Node::operator*(Node& b)
{
    Mat resultMat = *(this->data) * (*(b.data));
    Node out(std::make_shared<Mat>(resultMat));
    
    out.backward = [&]()
    {
        Mat thisGrad = *(this->grad) + (*(out.grad) * (b.data->T()));
        Mat bGrad = *(b.grad) + (this->data->T() * *(out.grad));
        this->grad = std::make_shared<Mat>(thisGrad);
        b.grad = std::make_shared<Mat>(bGrad);
    };
    return out;
}