#include "MNISTReader.h"
#include "DataSetReader.h"

int main()
{
    DataSetReader* p = new MNISTReader("../datasets/mnist_train.csv", 2);
    std::vector<std::vector<float>> l = p->readData();
    std::cout << l.size() << std::endl;
    std::vector<std::vector<float>> q = p->readData();
    return 0;
}