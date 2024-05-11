add_library(DataSetReader CSVReader.cpp DataSet.cpp)

target_link_libraries(DataSetReader PRIVATE IOUtils BuildingBlocks)

target_include_directories(DataSetReader PUBLIC
    ${PROJECT_SOURCE_DIR}/ioutils
    ${PROJECT_SOURCE_DIR}/layers/buildingblocks)