cmake_minimum_required(VERSION 3.0)

project(4a-engine)

set (BUILD_GLEW OFF)
#set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_BUILD_TYPE "Release")
#set (CMAKE_AUTOGEN_VERBOSE ON)
#set (CMAKE_VERBOSE_MAKEFILE ON)
include(variables.cmake)

include_directories(${INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -Wall")
add_compile_options(-lopengl32)
add_compile_options(-lm)

add_executable(4a-engine ${MAIN_SRC})

#modules
add_subdirectory(${LIB_DIR})
target_link_libraries(4a-engine index-buffer)
target_link_libraries(4a-engine vertex-buffer)
target_link_libraries(4a-engine vertex-array)
target_link_libraries(4a-engine vertex-layout)
target_link_libraries(4a-engine renderer)
target_link_libraries(4a-engine camera)

#external libs and modules
add_subdirectory(${EXTERNALS_DIR})

target_link_libraries(4a-engine ${GLEW_STATIC_LIB})
target_link_libraries(4a-engine ${GLFW_STATIC_LIB})
target_link_libraries(4a-engine ${SOIL_STATIC_LIB})
target_link_libraries(4a-engine ${GLM_STATIC_LIB})
target_link_libraries(4a-engine opengl32)
target_link_libraries(4a-engine m)