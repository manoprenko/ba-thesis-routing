cmake_minimum_required(VERSION 3.19)
project(algorithm)

add_library(${PROJECT_NAME}
    clustering/dsu.cpp
    clustering/edge_weight.cpp

    square_dijkstra.cpp
    set_dijkstra.cpp
    pq_dijkstra.cpp
    bfs.cpp
    bfs_dag.cpp
    limited_dijkstra.cpp
    cluster_dijkstra.cpp
)
target_link_libraries(${PROJECT_NAME} graph util)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
