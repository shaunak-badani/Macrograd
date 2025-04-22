#include "Vec4D.h"
#include "Node4D.h"

int main(int argc, char** argv)
{

    std::vector<std::vector<svf>> p = std::vector<std::vector<svf>>(4, 
            std::vector<svf>(5, 
            svf(6, std::vector<float>(7, 0))));

    std::shared_ptr<Vec4D> q = std::make_shared<Vec4D>(p);

    std::shared_ptr<Node4D> s = std::make_shared<Node4D>(q);

    
    std::cout << std::endl;
    return 0;
}