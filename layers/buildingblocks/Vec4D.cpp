#include "Vec4D.h"


Vec4D::Vec4D(std::vector<std::vector<svf>> p)
{
    this->vec = p;
}

std::vector<int> Vec4D::getShape() const
{
    int m = this->vec.size();

    if(!m)
        return {0, 0, 0, 0};
    
    int n = this->vec[0].size();

    if(!n)
        return {0, 0, 0, 0};

    int o = this->vec[0][0].size();

    if(!o)
        return {0, 0, 0, 0};

    int p = this->vec[0][0][0].size();

    return { m, n, o, p };
}

std::shared_ptr<Vec4D> Vec4D::zeros_like()
{
    std::vector<int> shape = this->getShape();

    int m = shape.at(0);
    int n = shape.at(1);
    int o = shape.at(2);
    int p = shape.at(3);
    std::vector<std::vector<svf>> current = std::vector<std::vector<svf>>(m, 
        std::vector<svf>(n, 
        svf(o, std::vector<float>(p, 0))));

    return std::make_shared<Vec4D>(current);
}
