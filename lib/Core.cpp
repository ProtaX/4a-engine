#include "Core.hpp"

void glGetErrors(int line) {
    while (GLenum error = glGetError()) 
        std::cout << "[OpenGL error]: 0x" << std::hex << error << " on line " << std::dec << __LINE__ << "\n";
}

void glClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}