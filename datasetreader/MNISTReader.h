#include "DataSetReader.h"
#include <fstream>

class MNISTReader : public DataSetReader
{
    private:
        std::ifstream myfile;

    public:
        std::vector<std::vector<float>> readData() override;
        MNISTReader(int batch_size);
};