cmake_minimum_required(VERSION 3.19)
project(testing)

add_library(${PROJECT_NAME} validator.cpp solution_family.cpp stats.cpp)
target_link_libraries(${PROJECT_NAME} graph algorithm)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
