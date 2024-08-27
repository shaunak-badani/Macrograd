#ifndef MAT_UTILS_H
#define MAT_UTILS_H

#include "Mat.h"
#include <memory>

class MatUtils
{
    public:
        static Mat crossCorrelate(Mat a, Mat b);
};

#endif