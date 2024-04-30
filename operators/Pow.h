#ifndef POW_H
#define POW_H
#include "Operator.h"
#include "Mat.h"


class Pow : public Operator
{
    int exponent;

    public: 
        Pow(int power)
        {
            this->exponent = power;
        }

    std::shared_ptr<Mat> calculate(std::shared_ptr<Mat> operand) override;

    std::shared_ptr<Mat> gradient(std::shared_ptr<Node> operand, std::shared_ptr<Node> out) override;
};

#endif