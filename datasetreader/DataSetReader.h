#ifndef DATASET_READER_H
#define DATASET_READER_H

#include <iostream>
#include <vector>

class DataSetReader
{
    protected:
        int batch_size;

        std::vector<float> split_string(std::string stringValue, char delimiter);

        std::vector<float> split_comma_separated_string(std::string stringValue);

    public:

        virtual std::vector<std::vector<float>> readData() = 0;
};

#endif