#include "Node.h"
#include "Mat.h"

Node::Node(Mat* paramData)
{
    this->data = paramData;
    this->grad = new Mat(*paramData, 0.0);
}
