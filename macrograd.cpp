#include "CSVReader.h"
#include "DataSetReader.h"

int main()
{
    DataSetReader* p = new CSVReader("../datasets/mnist_train.csv", 2);
    std::vector<std::vector<float>> l = p->readData();
    std::cout << l.size() << std::endl;
    std::vector<std::vector<float>> q = p->readData();
    return 0;
}