#ifndef TAN_H
#define TAN_H
#include "Operator.h"
#include "Mat.h"


class TanH : public Operator
{
    Mat calculate(Mat* operand) override;

    Mat gradient(Node* operand, Node* out) override;
};

#endif