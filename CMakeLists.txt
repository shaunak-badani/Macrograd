cmake_minimum_required(VERSION 3.10)

project(Macrograd VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(datasetreader)

add_executable(${PROJECT_NAME} macrograd.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC DataSetReader)

target_include_directories(${PROJECT_NAME} PUBLIC 
                            "${PROJECT_SOURCE_DIR}/datasetreader")

include(CTest) # We include CTest which is part of CMake
enable_testing()

add_test(Test_0, "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}")

# Adding test folders:
add_subdirectory(ioutils)
add_subdirectory(tests)
add_subdirectory(buildingblocks)
add_subdirectory(operators)

