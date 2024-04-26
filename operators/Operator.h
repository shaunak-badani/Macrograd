#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include <vector>
#include <functional>
#include "Node.h"
#include "Mat.h"
#include <unordered_set>
#include <algorithm>

class Operator
{
    public: 
        virtual Mat calculate(Mat* operand) = 0;

        virtual Mat gradient(Node* operand, Node* out) = 0;

        // a function that propagates the gradient to 
        void propagateGradientBackward(Node* operand, Node* out);

        Node* operate(Node* a);
};

#endif