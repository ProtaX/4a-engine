cmake_minimum_required(VERSION 3.0)

include(../variables.cmake)
include_directories(${INCLUDE_DIR})

add_executable(test test.cpp)
target_link_libraries(test Catch2)

add_executable(VLTest Lab5Test.cpp)
target_link_libraries(VLTest Catch2)
target_link_libraries(VLTest vertex-layout)
target_link_libraries(VLTest vertex-buffer)
target_link_libraries(VLTest camera)