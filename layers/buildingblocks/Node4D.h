#ifndef VALUE_4D_H
#define VALUE_4D_H
#include <vector>
#include <iostream>
#include <functional>
#include <memory>
#include "Mat.h"
#include <unordered_set>
#include "Vec4D.h"

class Node4D
{
    public:
        std::unordered_set<std::shared_ptr<Node4D>> previous;
        std::shared_ptr<Vec4D> data;
        std::shared_ptr<Vec4D> grad;
        std::function<void(void)> backward;
        Node4D(std::shared_ptr<Vec4D> paramData);
        Node4D(std::shared_ptr<Vec4D> paramData, std::unordered_set<std::shared_ptr<Node4D>> previous);

        // friend std::shared_ptr<Node> operator+(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
        // friend std::shared_ptr<Node> operator-(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
        // friend std::shared_ptr<Node> operator*(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
        // friend std::shared_ptr<Node> operator/(std::shared_ptr<Node> a, float b);
        
        // friend std::shared_ptr<Node> sum(std::shared_ptr<Node> a);

        // friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);
};

#endif