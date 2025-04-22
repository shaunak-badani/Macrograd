#ifndef VEC_4D_H
#define VEC_4D_H
#include "Vec.h"
#include "Mat.h"

class Vec4D : public Vec
{
    private:
        std::vector<std::vector<svf>> vec;

    public:
        Vec4D(std::vector<std::vector<svf>> piece);

        std::vector<int> getShape() const override;
        
        std::shared_ptr<Vec4D> zeros_like();
};

#endif