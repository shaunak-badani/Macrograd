#include "LayerUtils.h"
#include "Node.h"
#include <iostream>
#include <memory>


void LayerUtils::buildTopoGraph(std::shared_ptr<Node> root)
{
    if(this->visited.contains(root))
        return;

    for(std::shared_ptr<Node> child : root->previous)
    {
        buildTopoGraph(child);
    }
    this->visited.insert(root);

    // Don't call backward for leaf nodes
    if(!root->previous.empty())
        this->orderedNodes.push_back(root);
}

void LayerUtils::backward(std::shared_ptr<Node> root)
{
    this->visited = std::unordered_set<std::shared_ptr<Node>>();
    root->grad->assignValue(1.0);
    this->buildTopoGraph(root);

    std::reverse(this->orderedNodes.begin(), this->orderedNodes.end());
    std::cout << this->orderedNodes.size() << std::endl;
    for(std::shared_ptr<Node> nodePtr : this->orderedNodes) {
        if(!nodePtr) 
            throw std::runtime_error("Attempting to dereference a null pointer in LayerUtils!");

        // Dereference nodePtr safely since it's not null
        std::shared_ptr<Node> node = nodePtr;
        std::cout << *(nodePtr->data) << std::endl;
        std::cout << *(nodePtr->grad) << std::endl;
        if(!(nodePtr->backward))
            throw std::runtime_error("Backward function not defined for this node!");

        nodePtr->backward();
    }
}
