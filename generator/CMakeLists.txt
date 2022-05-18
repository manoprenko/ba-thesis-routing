cmake_minimum_required(VERSION 3.19)
project(generator)

add_library(${PROJECT_NAME}
    distribution.cpp
    normal_distribution.cpp
    discrete_distribution.cpp

    random.cpp
    grid.cpp
    dual_homed.cpp
    fat_tree.cpp
)

target_link_libraries(${PROJECT_NAME} util graph)
