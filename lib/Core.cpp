#include "Core.hpp"

namespace fae {

void glGetErrors(int line, const char* file) {
    while (GLenum error = glGetError()) 
        std::cout << "[OpenGL error]: 0x" << std::hex << error << " " <<  file << " on line " << std::dec << line << "\n";
}

void glClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

std::string GetWorkingDirectory() {
    char absoluteExePath[256];
    GetCurrentDirectoryA(256, absoluteExePath);
    int absPathLen = strlen(absoluteExePath);
    #ifdef TEST_BUILD
        absoluteExePath[absPathLen - strlen("build")] = '\0';
    #endif
    std::string path = std::string(absoluteExePath);
    return path;
}

}