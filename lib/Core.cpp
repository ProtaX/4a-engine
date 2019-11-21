#include "Core.hpp"

void glGetErrors(int line, const char* file) {
    while (GLenum error = glGetError()) 
        std::cout << "[OpenGL error]: 0x" << std::hex << error << " " <<  file << " on line " << std::dec << line << "\n";
}

void glClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}