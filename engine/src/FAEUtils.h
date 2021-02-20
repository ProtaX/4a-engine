#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include "windows.h"

#define TEST_BUILD

namespace fae {

#define GLCall(x) \
    x; \
    glGetErrors(__LINE__, __FILE__); \
    glClearErrors() \

#define GLFWCall(x) \
    x; \
    do { \
      const char* errMsg; \
      const char** errMsgLoc = &errMsg; \
      int code = glfwGetError(errMsgLoc); \
      if (code != GLFW_NO_ERROR) { \
        std::cout << "GLFW error: " << errMsg << std::endl; \
        glfwTerminate(); \
      } \
    } while (0)     \

inline void glGetErrors(int line, const char* file) {
  while (GLenum error = glGetError())
    std::cout << "[OpenGL error]: 0x" << std::hex << error << " " <<  file << " on line " << std::dec << line << "\n";
}

inline void glClearErrors() {
  while (glGetError() != GL_NO_ERROR) { }
}

[[nodiscard]] inline std::string GetWorkingDirectory() {
  char absoluteExePath[256];
  GetCurrentDirectoryA(256, absoluteExePath);
#ifdef TEST_BUILD
  absoluteExePath[std::strlen(absoluteExePath) - std::strlen("cmake-build-debug/")] = '\0';
#endif
  std::string path = std::string(absoluteExePath);
  return path;
}

} // namespace fae
