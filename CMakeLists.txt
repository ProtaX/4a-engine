cmake_minimum_required(VERSION 3.0)

project(4a-engine)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
set(CMAKE_BUILD_TYPE "Debug")
#set (CMAKE_BUILD_TYPE "Release")
include(variables.cmake)

#external includes
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})
include_directories(${CATCH2_SINGLE_INCLUDE_DIR})
include_directories(${ENGINE_INCLUDE_DIR})
include_directories(${GAME_DIR})

add_executable(4a-engine ${MAIN_SRC})

#modules
add_subdirectory(${ENGINE_SRC_DIR})
target_link_libraries(4a-engine GameObject)
target_link_libraries(4a-engine IndexBuffer)
target_link_libraries(4a-engine VertexBuffer)
target_link_libraries(4a-engine VertexArray)
target_link_libraries(4a-engine VertexLayout)
target_link_libraries(4a-engine Renderer)
target_link_libraries(4a-engine Camera)
target_link_libraries(4a-engine GLShader)
target_link_libraries(4a-engine GameScene)
target_link_libraries(4a-engine Event)
target_link_libraries(4a-engine Texture)
target_link_libraries(4a-engine AnimatedTexture)
target_link_libraries(4a-engine DynamicGameObject)
target_link_libraries(4a-engine StaticGameObject)
target_link_libraries(4a-engine AnimatedGameObject)
target_link_libraries(4a-engine ControllableGameObject)

#externals
add_subdirectory(${EXTERNALS_DIR})
target_link_libraries(4a-engine soil)
target_link_libraries(4a-engine glew)
target_link_libraries(4a-engine glfw)
target_link_libraries(4a-engine glm_static)
target_link_libraries(4a-engine opengl32)
target_link_libraries(4a-engine m)

#tests
include(${ENGINE_TESTS_DIR}/Stub/Stub.cmake)
include(${ENGINE_TESTS_DIR}/Camera/CameraTest.cmake)
include(${ENGINE_TESTS_DIR}/VertexLayout/VertexLayoutTest.cmake)
include(${ENGINE_TESTS_DIR}/GameObject/StaticGameObjectTest.cmake)
include(${ENGINE_TESTS_DIR}/Shader/GLShaderTest.cmake)
