#include "Texture.hpp"
#include "game.cpp"

//Increments when a new Texture object is created 
GLuint fae::Texture::vaccant_tex_target = GL_TEXTURE0;

int main() {
    game();
    glfwTerminate();
}