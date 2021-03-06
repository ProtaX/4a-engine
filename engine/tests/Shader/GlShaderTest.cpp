#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <GlShader.hpp>
#include <string>

using namespace fae;

TEST_CASE("GlShader class", "[load]"){
  std::string vsSource = "#version 330 core \n\
  layout (location = 0) in vec3 position; \n\
  layout (location = 1) in vec3 color; \n\
  layout (location = 2) in vec2 texCoord; \n\
  out vec3 ourColor; \n\
  out vec2 TexCoord; \n\
  uniform int orientation; \n\
  uniform mat4 model; \n\
  uniform int is_transformable; \n\
  uniform mat4 proj; \n\
  uniform mat4 view; \n\
  void main() { \n\
    if (is_transformable == 1) { \n\
      gl_Position = proj * view * model * vec4(position, 1.0f); \n\
    } \n\
    else { \n\
      gl_Position = proj * view * vec4(position, 1.0f); \n\
    } \n\
    TexCoord.y = 1.0f - texCoord.y; \n\
    if (orientation == 1 && is_transformable == 1) { \n\
      TexCoord.x = 1.0f - texCoord.x; \n\
    } \n\
    else { \n\
      TexCoord.x = texCoord.x; \n\
    } \n\
    ourColor = color; \n\
  }";
  std::string fsSource = "#version 330 core \n\
  in vec3 ourColor; \n\
  in vec2 TexCoord; \n\
  out vec4 color; \n\
  uniform sampler2D ourTexture; \n\
  void main() { \n\
    color = texture(ourTexture, TexCoord); \n\
  }";
  GlShader shader;
  GLuint shaderProgram;
  shaderProgram = shader.LinkFromSource(vsSource, fsSource);
  REQUIRE(shaderProgram != 0);
}
