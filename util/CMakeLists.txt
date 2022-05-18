cmake_minimum_required(VERSION 3.19)
project(util)

add_library(${PROJECT_NAME} util.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
