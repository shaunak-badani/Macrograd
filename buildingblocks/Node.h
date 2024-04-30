#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <iostream>
#include <functional>
#include <memory>
#include "Mat.h"
class Node
{
    public:

        std::shared_ptr<Mat> data;
        std::shared_ptr<Mat> grad;
        std::function<void(void)> backward;
        Node(std::shared_ptr<Mat> paramData);

        Node operator+(Node& b);
        Node operator*(Node& b);

};

#endif