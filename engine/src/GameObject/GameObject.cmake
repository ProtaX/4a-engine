cmake_minimum_required(VERSION 3.0)

add_library(GameObject ${ENGINE_SRC_DIR}/GameObject/GameObject.cpp)
add_library(DynamicGameObject ${ENGINE_SRC_DIR}/GameObject/DynamicGameObject.cpp)
add_library(StaticGameObject ${ENGINE_SRC_DIR}/GameObject/StaticGameObject.cpp)
add_library(AnimatedGameObject ${ENGINE_SRC_DIR}/GameObject/AnimatedGameObject.cpp)
add_library(ControllableGameObject ${ENGINE_SRC_DIR}/GameObject/ControllableGameObject.cpp)