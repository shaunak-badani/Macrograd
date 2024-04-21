#ifndef DATASET_READER_H
#define DATASET_READER_H

#include <iostream>
#include <vector>

class DataSetReader
{
    protected:
        int batch_size;

    public:

        virtual std::vector<std::vector<float>> readData() = 0;
};

#endif