cmake_minimum_required(VERSION 3.0)

include(../variables.cmake)
include_directories(${INCLUDE_DIR})

add_executable(test test.cpp)
target_link_libraries(test Catch2)

add_executable(VLTest VertexLayoutTest.cpp)
target_link_libraries(VLTest Catch2)