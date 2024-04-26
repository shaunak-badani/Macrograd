#include "Operator.h"

void Operator::propagateGradientBackward(Node* operand, Node* out)
{
    Mat grad = gradient(operand, out);
    svf outGrad = out->grad->getPiece();
    Mat gradToBeAdded = grad.mapFunction([=](int i, int j, float value){
        return value * outGrad[i][j];
    });
    Mat k = *(operand->grad) + gradToBeAdded;
    operand->grad = new Mat(k);
}

Node* Operator::operate(Node* a)
{
    Node* out = new Node(new Mat(calculate(a->data)));
    out->backward = [=](){ propagateGradientBackward(a, out); };
    return out;
}