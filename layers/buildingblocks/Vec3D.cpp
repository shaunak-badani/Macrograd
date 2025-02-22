#include "Vec3D.h"


Vec3D::Vec3D(std::vector<svf> p)
{
    this->vec = p;
}

std::vector<int> Vec3D::getShape() const
{
    int m = this->vec.size();

    if(!m)
        return {0, 0, 0};
    
    int n = this->vec[0].size();

    if(!n)
        return {0, 0, 0};

    int o = this->vec[0][0].size();

    return { m, n, o };
}