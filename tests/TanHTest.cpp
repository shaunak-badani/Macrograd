#include "Mat.h"
#include "TanH.h"
#include "Operator.h"
#include "Node.h"
#include <gtest/gtest.h>


TEST(TanH, tanh)
{
    svf p = {
        {1.0, 2.0},
        {3.0, 4.0}
    };

    Mat a(p);
    Node* input = new Node(&a);
    Operator* tanh = new TanH();
    Node* y = tanh->operate(input);

    svf expectedOutput = {
        {0.76159, 0.96402},
        {0.99505, 0.9993292}
    };

    y->data->mapFunction([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedOutput[i][j] - value) < 1e-4);
        return 1.0;
    }); 

    y->grad->assignValue(1.0);

    y->backward();

    svf expectedGrad = {
        {0.419974376, 0.070650825},
        {0.009866038, 0.00134095}
    };

    input->grad->mapFunction([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGrad[i][j] - value) < 1e-3);
        return 1.0;
    });


}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}


