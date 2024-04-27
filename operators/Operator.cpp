#include "Operator.h"

void Operator::propagateGradientBackward(std::shared_ptr<Node> operand, std::shared_ptr<Node> out)
{
    std::shared_ptr<Mat> grad = gradient(operand, out);
    svf outGrad = out->grad->getPiece();
    std::shared_ptr<Mat> gradToBeAdded = grad.get()->mapFunction([=](int i, int j, float value){
        return value * outGrad[i][j];
    });
    *(operand->grad) += *gradToBeAdded.get();
}

std::shared_ptr<Node> Operator::operate(std::shared_ptr<Node> a)
{
    std::shared_ptr<Node> out = std::make_shared<Node>(calculate(a->data));
    out->backward = [=](){ 
        propagateGradientBackward(a, out); 
    };
    return out;
}