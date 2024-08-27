#ifndef MAT_UTILS_H
#define MAT_UTILS_H

#include "Mat.h"
#include <memory>

class MatUtils
{
    public:
        static std::shared_ptr<Mat> crossCorrelate(std::shared_ptr<Mat> a, std::shared_ptr<Mat> b);
};

#endif