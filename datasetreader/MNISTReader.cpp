#include "MNISTReader.h"
#include "IOUtils.h"

MNISTReader::MNISTReader(std::string filePath, int batch_size)
{
    this->batch_size = batch_size;
    this->filePath = filePath;
    this->filePos = 0;
}

std::vector<std::vector<float>> MNISTReader::readData()
{
    std::vector<std::vector<float>> mnistData;
    std::ifstream myfile;
    if(!myfile.is_open())
    {
        myfile.open(this->filePath);
    }
    std::string currentDataPoint;
    myfile.seekg(this->filePos);

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

    this->filePos = myfile.tellg();
    myfile.close();

    return mnistData;
    
}