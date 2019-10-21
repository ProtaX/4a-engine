#include "Renderer.hpp"

void GLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

void GLGetErrors(int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL error]: 0x" << std::hex << error << " on line " << std::dec << line << "\n";
    }
}