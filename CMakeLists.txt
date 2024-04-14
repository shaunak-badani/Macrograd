cmake_minimum_required(VERSION 3.10)

project(Macrograd VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO 2: Use add_subdirectory() to add MathFunctions to this project
add_subdirectory(datasetreader)

# add the executable
add_executable(macrograd macrograd.cpp)

# TODO 3: Use target_link_libraries to link the library to our executable
target_link_libraries(macrograd PUBLIC DataSetReader)

# add the binary tree to the search path for include files
target_include_directories(macrograd PUBLIC 
                            "${PROJECT_SOURCE_DIR}/datasetreader")
