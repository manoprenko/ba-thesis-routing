cmake_minimum_required(VERSION 3.19)
project(graph)

add_library(${PROJECT_NAME} graph.cpp graph_builder.cpp)
target_link_libraries(${PROJECT_NAME} util)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
