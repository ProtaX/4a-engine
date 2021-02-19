cmake_minimum_required(VERSION 3.0)

set(CAMERA_TEST_SRC
        ${TESTS_DIR}/Camera/CameraTest.cpp
        ${LIB_DIR}/Camera.cpp)

add_executable(CameraTest ${CAMERA_TEST_SRC})
target_link_libraries(CameraTest Catch2)
