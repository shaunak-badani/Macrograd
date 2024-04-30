#include "MeanSquaredError.h"
#include <memory>
#include <iostream>
#include "Operator.h"

MeanSquaredError::MeanSquaredError()
{
    this->powerOperator = std::make_shared<Operator>(2);
}


std::shared_ptr<Mat> MeanSquaredError::operator()(std::shared_ptr<Node> actualValues, 
        std::shared_ptr<Node> expectedValues)
{
    std::shared_ptr<Node> p = (actualValues.get() - expectedValues.get());
    return this->powerOperator->operate(actualValues - expectedValues);
}


