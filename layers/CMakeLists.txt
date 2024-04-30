set(TARGET_NAME Layers)

project(Layers VERSION 1.0)

add_library(${TARGET_NAME} Layer.cpp)

add_subdirectory(buildingblocks)
add_subdirectory(operators)
# add_subdirectory(lossfn)

target_link_libraries(${TARGET_NAME} PRIVATE BuildingBlocks Operators)
target_include_directories(${TARGET_NAME} PUBLIC 
        ./buildingblocks
        ./operators)

target_link_libraries(${TARGET_NAME} 
        PRIVATE BuildingBlocks Operators)
