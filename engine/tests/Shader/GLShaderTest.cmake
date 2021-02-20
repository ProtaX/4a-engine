cmake_minimum_required(VERSION 3.0)

set(GL_SHADER_TEST_SRC
        ${ENGINE_SRC_DIR}/GLShader.cpp
        ${ENGINE_TESTS_DIR}/Shader/GLShaderTest.cpp)

add_executable(GLShaderTest ${GL_SHADER_TEST_SRC})
target_link_libraries(GLShaderTest Catch2)
target_link_libraries(GLShaderTest glew)
target_link_libraries(GLShaderTest glm_static)
