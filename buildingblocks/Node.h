#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <iostream>
#include <functional>
#include "Mat.h"
class Node
{
    public:

        Mat* data;
        Mat* grad;
        std::function<void(void)> backward;
        Node(Mat* paramData);

        Node operator+(Node& b);

};

#endif