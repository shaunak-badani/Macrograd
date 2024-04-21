add_library(DataSetReader MNISTReader.cpp)

target_link_libraries(DataSetReader PRIVATE IOUtils)

target_include_directories(DataSetReader PUBLIC ${PROJECT_SOURCE_DIR}/ioutils)