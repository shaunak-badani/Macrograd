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

        std::shared_ptr<Node> operator+(Node& b);
        std::shared_ptr<Node> operator*(Node& b);

};

#endif