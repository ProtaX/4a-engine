cmake_minimum_required(VERSION 3.0)

set(VERTEX_LAYOUT_TEST_SRC
        ${ENGINE_TESTS_DIR}/VertexLayout/VertexLayoutTest.cpp
        ${ENGINE_SRC_DIR}/VertexLayout.cpp
        ${ENGINE_SRC_DIR}/VertexBuffer.cpp)

add_executable(VertexLayoutTest ${VERTEX_LAYOUT_TEST_SRC})
target_link_libraries(VertexLayoutTest Catch2)
target_link_libraries(VertexLayoutTest glew)
