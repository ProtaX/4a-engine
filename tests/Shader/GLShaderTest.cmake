cmake_minimum_required(VERSION 3.0)

set(GL_SHADER_TEST_SRC
        ${LIB_DIR}/GLShader.cpp
        ${TESTS_DIR}/Shader/GLShaderTest.cpp)

add_executable(GLShaderTest ${GL_SHADER_TEST_SRC})
target_link_libraries(GLShaderTest Catch2)
target_link_libraries(GLShaderTest glew)
target_link_libraries(GLShaderTest glm_static)
