#include "DataSetReader.h"
#include <fstream>

class MNISTReader : public DataSetReader
{
    private:
        
        std::string filePath;
        std::streampos filePos;

    public:
        std::vector<std::vector<float>> readData() override;
        MNISTReader(std::string filePath, int batch_size);
};