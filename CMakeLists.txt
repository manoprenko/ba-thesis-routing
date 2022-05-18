cmake_minimum_required(VERSION 3.19)
project(thesis)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wno-sign-compare -Werror)
add_compile_options(-Ofast)

add_subdirectory(util)
add_subdirectory(graph)
add_subdirectory(generator)

add_subdirectory(algorithm)
add_subdirectory(testing)

add_executable(main main.cpp)
target_link_libraries(main graph generator util algorithm testing)
