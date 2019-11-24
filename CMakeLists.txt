cmake_minimum_required(VERSION 3.0)

project(4a-engine)

set (CMAKE_BUILD_TYPE "Debug")
#set (CMAKE_BUILD_TYPE "Release")
include(variables.cmake)

include_directories(${INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})
include_directories(${CATCH2_SINGLE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
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
target_link_libraries(4a-engine game-object)
target_link_libraries(4a-engine core)
target_link_libraries(4a-engine game-scene)

#externals
add_subdirectory(${EXTERNALS_DIR})
target_link_libraries(4a-engine ${SOIL_STATIC_LIB})
target_link_libraries(4a-engine glew)
target_link_libraries(4a-engine glfw)
target_link_libraries(4a-engine glm_static)
target_link_libraries(4a-engine opengl32)
target_link_libraries(4a-engine m)

#tests
include(${TESTS_DIR}/Tests.cmake)