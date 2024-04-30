set(TARGET_NAME Layers)

add_library(${TARGET_NAME} Layer.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE BuildingBlocks Operators)
target_include_directories(${TARGET_NAME} PUBLIC 
        ./buildingblocks
        ./operators)

target_link_libraries(${TARGET_NAME} 
        PRIVATE BuildingBlocks Operators)
