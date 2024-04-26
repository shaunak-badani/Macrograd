#include "Node.h"
#include "Mat.h"

Node::Node(Mat* paramData)
{
    this->data = paramData;
    this->grad = new Mat(*paramData, 0.0);
}


Node Node::operator+(Node& b)
{
    Mat resultMat = *(this->data) + *(b.data);
    Node out(new Mat(resultMat));
    
    out.backward = [&]()
    {
        Mat thisGrad = *(out.grad) + *(b.grad);
        Mat bGrad = *(out.grad) + *(this->grad);
        this->grad = new Mat(thisGrad);
        b.grad = new Mat(bGrad);
    };
    return out;
}