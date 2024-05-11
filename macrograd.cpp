#include "CSVReader.h"
#include "DataSetReader.h"
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<DataSetReader> p = std::make_shared<CSVReader>("../datasets/mnist_train.csv", 5);
    std::shared_ptr<DataSet> dataSet = p->readData();
    std::cout << *(dataSet->getData()->data.get()) << std::endl;
    std::cout << "Label : " << std::endl;
    std::cout << *(dataSet->getLabels()->data.get()) << std::endl;
    return 0;
}