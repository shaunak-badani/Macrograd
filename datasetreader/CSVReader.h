#include "DataSetReader.h"
#include <fstream>
#include "DataSet.h"

class CSVReader : public DataSetReader
{
    private:
        
        std::string filePath;
        std::streampos filePos;

    public:
        std::shared_ptr<DataSet> readData() override;
        CSVReader(std::string filePath, int batch_size);
};