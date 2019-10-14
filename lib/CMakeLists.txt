cmake_minimum_required(VERSION 3.0)

add_library(index-buffer ${LIB_DIR}/IndexBuffer.cpp)
add_library(vertex-buffer ${LIB_DIR}/VertexBuffer.cpp)
add_library(vertex-array ${LIB_DIR}/VertexArray.cpp)
add_library(vertex-layout ${LIB_DIR}/VertexLayout.cpp)
add_library(renderer ${LIB_DIR}/Renderer.cpp)

target_include_directories(index-buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(vertex-buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(vertex-array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(vertex-layout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})