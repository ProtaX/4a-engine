#include "Texture.hpp"
#include "game.cpp"

// Increments when a new Texture object is created
GLuint fae::Texture::VACCANT_TEX_TARGET = GL_TEXTURE0;

int main() {
  game();
  glfwTerminate();
}
