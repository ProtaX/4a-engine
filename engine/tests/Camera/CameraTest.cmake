cmake_minimum_required(VERSION 3.0)

set(CAMERA_TEST_SRC
        ${ENGINE_TESTS_DIR}/Camera/CameraTest.cpp
        ${ENGINE_SRC_DIR}/Camera.cpp)

add_executable(CameraTest ${CAMERA_TEST_SRC})
target_link_libraries(CameraTest Catch2)
