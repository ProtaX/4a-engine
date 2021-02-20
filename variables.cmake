cmake_minimum_required(VERSION 3.0)

set (PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (ENGINE_DIR ${PROJECT_DIR}/engine)
set (ENGINE_SRC_DIR ${ENGINE_DIR}/src)
set (ENGINE_TESTS_DIR ${ENGINE_DIR}/tests)
set (ENGINE_INCLUDE_DIR ${ENGINE_DIR}/include)
set (GAME_DIR ${PROJECT_DIR}/game)

set (GLM_INCLUDE_DIR ${PROJECT_DIR}/externals/glm)
set (GLEW_INCLUDE_DIR ${PROJECT_DIR}/externals/glew2_protax/include)
set (GLFW_INCLUDE_DIR ${PROJECT_DIR}/externals/glfw/include)
set (SOIL_INCLUDE_DIR ${PROJECT_DIR}/externals/soil/inc/SOIL)
set (CATCH2_INCLUDE_DIR ${PROJECT_DIR}/externals/Catch2/include)
set (CATCH2_SINGLE_INCLUDE_DIR ${PROJECT_DIR}/externals/Catch2/single_include)
set (EXTERNALS_DIR ${PROJECT_DIR}/externals)

set (MAIN_SRC ${ENGINE_SRC_DIR}/main.cpp)