cmake_minimum_required(VERSION 3.0)

set(STATIC_GAME_OBJECT_TEST_SRC
        ${ENGINE_TESTS_DIR}/GameObject/StaticGameObjectTest.cpp
        ${ENGINE_SRC_DIR}/GameObject/StaticGameObject.cpp
        ${ENGINE_SRC_DIR}/GameObject/GameObject.cpp
        )

add_executable(StaticGameObjectTest ${STATIC_GAME_OBJECT_TEST_SRC})
target_link_libraries(StaticGameObjectTest IndexBufferStub)
target_link_libraries(StaticGameObjectTest VertexBufferStub)
target_link_libraries(StaticGameObjectTest VertexArrayStub)
target_link_libraries(StaticGameObjectTest TextureStub)

target_link_libraries(StaticGameObjectTest vertex-layout)
target_link_libraries(StaticGameObjectTest event)
target_link_libraries(StaticGameObjectTest m)
