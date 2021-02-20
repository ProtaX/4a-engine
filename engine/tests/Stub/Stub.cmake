cmake_minimum_required(VERSION 3.0)

set(CWD ${ENGINE_TESTS_DIR}/Stub)

add_library(VertexArrayStub ${CWD}/VertexArrayStub.cpp)
add_library(VertexBufferStub ${CWD}/VertexBufferStub.cpp)
add_library(IndexBufferStub ${CWD}/IndexBufferStub.cpp)
add_library(TextureStub ${CWD}/TextureStub.cpp)
