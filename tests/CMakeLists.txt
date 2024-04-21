cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME IOUtils_test)

# Fetching Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# IOUtils
add_executable(${TARGET_NAME} Test.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE IOUtils GTest::gtest_main GTest::gmock_main)


target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/ioutils)
message("target file: ${TARGET_FILE}")


add_test(NAME ${TARGET_NAME} COMMAND $<TARGET_FILE:${TARGET_NAME}>)