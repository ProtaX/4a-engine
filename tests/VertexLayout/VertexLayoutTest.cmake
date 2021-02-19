cmake_minimum_required(VERSION 3.0)

set(VERTEX_LAYOUT_TEST_SRC
        ${TESTS_DIR}/VertexLayout/VertexLayoutTest.cpp
        ${LIB_DIR}/VertexLayout.cpp
        ${LIB_DIR}/VertexBuffer.cpp)

add_executable(VertexLayoutTest ${VERTEX_LAYOUT_TEST_SRC})
target_link_libraries(VertexLayoutTest Catch2)
target_link_libraries(VertexLayoutTest glew)
