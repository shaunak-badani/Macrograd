#ifndef VEC_3D_H
#define VEC_3D_H
#include "Vec.h"
#include "Mat.h"

class Vec3D : public Vec
{
    private:
        std::vector<svf> vec;

    public:
        Vec3D(std::vector<svf> piece);

        std::vector<int> getShape() const override;

};

#endif