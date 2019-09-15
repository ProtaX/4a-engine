cmake_minimum_required(VERSION 3.0)

project(4a-engine)

include(variables.cmake)

include_directories(${INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -Wall")
add_compile_options(-lopengl32)

#modules
add_subdirectory(${LIB_DIR})

#external libs and modules
add_subdirectory(${EXTERNALS_DIR})

add_executable(4a-engine ${MAIN_SRC})

target_link_libraries(4a-engine ${GLEW_STATIC_LIB})
target_link_libraries(4a-engine ${GLFW_STATIC_LIB})
target_link_libraries(4a-engine opengl32)