#include <gtest/gtest.h>
#include "DataSetReader.h"
#include "CSVReader.h"
#include <iostream>
#include <memory>
#include "DataSetsPathConfig.h"

void expect_pair_eq(std::pair<int, int> expectedPair, std::pair<int, int> actualPair)
{
    EXPECT_EQ(expectedPair.first, actualPair.first);
    EXPECT_EQ(expectedPair.second, actualPair.second);
}


TEST(DataSetReader, CSVReader)
{
    std::string filePath = DATASETS_PATH + "/mnist_train.csv";
    std::shared_ptr<DataSetReader> dataSetReader = std::make_shared<CSVReader>(
        filePath,
        32
    );

    std::shared_ptr<DataSet> dataSet = dataSetReader->readNextBatch();

    std::pair<int, int> dataShape = dataSet->getData()->data->getShape();
    std::pair<int, int> labelsShape = dataSet->getLabels()->data->getShape();

    expect_pair_eq(dataShape, std::pair<int, int>({32, 784}));
    expect_pair_eq(labelsShape, std::pair<int, int>({32, 1}));
}

TEST(DataSetReader, CSVReaderNegativeTest)
{
    std::string filePath = DATASETS_PATH + "doesNotExistFileName";

    EXPECT_THROW(
        std::make_shared<CSVReader>(filePath,2),
        std::runtime_error
    );
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}