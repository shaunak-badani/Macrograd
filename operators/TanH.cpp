#include "TanH.h"
#include <math.h>

Mat TanH::calculate(Mat* operand)
{
    Mat output = operand->mapFunction([](int i, int j, float value) { return tanh(value); } );
    return output;
}

Mat TanH::gradient(Node* operand, Node* out)
{
    Mat output = operand->data->mapFunction([](int i, int j, float value) { 
        return 1 - pow(tanh(value), 2);
    });
    return output;
}