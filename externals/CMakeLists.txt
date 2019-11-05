cmake_minimum_required(VERSION 3.0)

add_subdirectory(${EXTERNALS_DIR}/glfw)

add_subdirectory(${EXTERNALS_DIR}/glew-2.0.0/build/cmake)

add_subdirectory(${EXTERNALS_DIR}/soil)

add_subdirectory(${EXTERNALS_DIR}/glm)

add_subdirectory(${EXTERNALS_DIR}/Catch2)