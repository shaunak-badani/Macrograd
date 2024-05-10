#include "DataSetReader.h"
#include <fstream>

class CSVReader : public DataSetReader
{
    private:
        
        std::string filePath;
        std::streampos filePos;

    public:
        std::vector<std::vector<float>> readData() override;
        CSVReader(std::string filePath, int batch_size);
};