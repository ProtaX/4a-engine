cmake_minimum_required(VERSION 3.0)

add_library(game-object ${LIB_DIR}/GameObject/GameObject.cpp)
add_library(dynamic-game-object ${LIB_DIR}/GameObject/DynamicGameObject.cpp)
add_library(static-game-object ${LIB_DIR}/GameObject/StaticGameObject.cpp)