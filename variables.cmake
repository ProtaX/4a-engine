cmake_minimum_required(VERSION 3.0)

set (PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (LIB_DIR ${PROJECT_DIR}/lib)

set (INCLUDE_DIR ${PROJECT_DIR}/include)

set (EXTERNALS_DIR ${PROJECT_DIR}/externals)

set (SRC_DIR ${PROJECT_DIR}/src)

set (MAIN_SRC ${SRC_DIR}/main.cpp)

set (GLEW_STATIC_LIB ${EXTERNALS_DIR}/glew-2.0.0/lib/libglew32.dll.a)
set (SOIL_STATIC_LIB ${EXTERNALS_DIR}/soil/libSOIL.a)

set (GLFW_STATIC_LIB ${PROJECT_DIR}/build/externals/glfw-3.3/src/libglfw3.a)
set (GLM_STATIC_LIB ${PROJECT_DIR}/build/externals/glm/glm/libglm_static.a)

