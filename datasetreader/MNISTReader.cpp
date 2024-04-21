#include "MNISTReader.h"
#include "IOUtils.h"

MNISTReader::MNISTReader(int batch_size)
{
    this->batch_size = batch_size;
}

std::vector<std::vector<float>> MNISTReader::readData()
{
    std::vector<std::vector<float>> mnistData;
    if(!myfile.is_open())
    {
        myfile.open("../datasets/mnist_train.csv");
    }
    std::string currentDataPoint;

    if(myfile.is_open())
    {
        for(int bufferedIndex = 0 ; bufferedIndex < this->batch_size && myfile.good() ; bufferedIndex++)
        {
            myfile >> currentDataPoint;
            mnistData.push_back(IOUtils::to_float(
                IOUtils::split_comma_separated_string(currentDataPoint)
            ));
        }
    }
    return mnistData;
    
}