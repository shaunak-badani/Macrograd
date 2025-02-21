#include "LayerUtils.h"
#include "Node.h"
#include <iostream>
#include <memory>
#define deb(x) std::cout<< (x)  << std::endl;


void LayerUtils::buildTopoGraph(std::shared_ptr<Node> root)
{
    if(this->visited.contains(root))
        return;

    // Don't call backward for leaf nodes
    // if(root->previous.empty())
    //     return;

    for(std::shared_ptr<Node> child : root->previous)
    {
        // deb(child);
        // std::cout << child->previous.size() << std::endl;
        buildTopoGraph(child);
    }

    this->visited.insert(root);
    this->orderedNodes.push_back(root);
}

void LayerUtils::backward(std::shared_ptr<Node> root)
{
    this->visited = std::unordered_set<std::shared_ptr<Node>>();
    this->orderedNodes = std::vector<std::shared_ptr<Node>>();
    root->grad->assignValue(1.0);
    this->buildTopoGraph(root);

    std::reverse(this->orderedNodes.begin(), this->orderedNodes.end());
    for(std::shared_ptr<Node> nodePtr : this->orderedNodes) {
        // deb(nodePtr);
        std::cout << nodePtr.get() << " " << nodePtr << std::endl;
        std::cout << "Previous: " << std::endl;
        for(std::shared_ptr<Node> prev : nodePtr->previous)
        {
            std::cout << prev.get() << " " << prev << std::endl;
        }
        std::cout << "===========" << std::endl;
        
        nodePtr->backward();
    }
}
