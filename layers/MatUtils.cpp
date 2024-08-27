#include "MatUtils.h"
#include "Mat.h"
#include <memory>

std::shared_ptr<Mat> MatUtils::crossCorrelate(std::shared_ptr<Mat> A, std::shared_ptr<Mat> B)
{
    std::vector<int> aShape = A->getShape();
    int m = aShape.at(0);
    int n = aShape.at(1);

    std::vector<int> bShape = B->getShape();

    int p = bShape.at(0);
    int q = bShape.at(1);

    std::pair<int, int> resultShape = {m - p + 1, n - q + 1};

    svf c = svf(resultShape.first, std::vector<float>(resultShape.second, 0));

    for(int i = 0 ; i < resultShape.first ; i++)
    {
        for(int j = 0 ; j < resultShape.second ; j++)
        {
            float val_ij = 0;

            for(int u = 0; u < p ; u++)
            {
                for(int v = 0 ; v < q ; v++)
                {
                    val_ij += A->at(i + u, j + v) * B->at(u, v);
                }
            }

            c[i][j] = val_ij;
        }
    }

    return std::make_shared<Mat>(c);
}