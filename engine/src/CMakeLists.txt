cmake_minimum_required(VERSION 3.0)

include_directories(${ENGINE_INCLUDE_DIR}/GameObject)

add_library(GLShader ${ENGINE_SRC_DIR}/GlShader.cpp)
add_library(IndexBuffer ${ENGINE_SRC_DIR}/IndexBuffer.cpp)
add_library(VertexBuffer ${ENGINE_SRC_DIR}/VertexBuffer.cpp)
add_library(VertexArray ${ENGINE_SRC_DIR}/VertexArray.cpp)
add_library(VertexLayout ${ENGINE_SRC_DIR}/VertexLayout.cpp)
add_library(Renderer ${ENGINE_SRC_DIR}/Renderer.cpp)
add_library(Camera ${ENGINE_SRC_DIR}/Camera.cpp)
add_library(GameScene ${ENGINE_SRC_DIR}/GameScene.cpp)
add_library(Event ${ENGINE_SRC_DIR}/Event.cpp)
add_library(Texture ${ENGINE_SRC_DIR}/Texture.cpp)
add_library(AnimatedTexture ${ENGINE_SRC_DIR}/AnimatedTexture.cpp)

include(${ENGINE_SRC_DIR}/GameObject/GameObject.cmake)