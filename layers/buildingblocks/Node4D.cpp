#include "Node4D.h"

Node4D::Node4D(std::shared_ptr<Vec4D> paramData, std::unordered_set<std::shared_ptr<Node4D>> previous)
{
    this->data = paramData;
    this->grad = paramData->zeros_like();
    this->previous = previous;
}

Node4D::Node4D(std::shared_ptr<Vec4D> paramData) : Node4D(paramData, std::unordered_set<std::shared_ptr<Node4D>>()) 
{

}


