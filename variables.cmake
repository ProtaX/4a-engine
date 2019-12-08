cmake_minimum_required(VERSION 3.0)

set (PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (LIB_DIR ${PROJECT_DIR}/lib)

set (INCLUDE_DIR ${PROJECT_DIR}/include)
set (GLM_INCLUDE_DIR ${PROJECT_DIR}/externals/glm)
set (GLEW_INCLUDE_DIR ${PROJECT_DIR}/externals/glew2_protax/include)
set (GLFW_INCLUDE_DIR ${PROJECT_DIR}/externals/glfw/include)
set (SOIL_INCLUDE_DIR ${PROJECT_DIR}/externals/soil/inc/SOIL)
set (CATCH2_INCLUDE_DIR ${PROJECT_DIR}/externals/Catch2/include)
set (CATCH2_SINGLE_INCLUDE_DIR ${PROJECT_DIR}/externals/Catch2/single_include)


set (EXTERNALS_DIR ${PROJECT_DIR}/externals)

set (TESTS_DIR ${PROJECT_DIR}/tests)

set (SRC_DIR ${PROJECT_DIR}/src)

set (MAIN_SRC ${SRC_DIR}/main.cpp)