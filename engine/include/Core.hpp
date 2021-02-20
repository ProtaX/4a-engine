#pragma once

#define TEST_BUILD

#include <stdlib.h>
#include <stdint.h>

#include <windows.h>
#include <iostream>
#include <memory>
#include <string>

#include <GL/glew.h>

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
    } while (0) \

#define RGBA_TEXTURE SOIL_LOAD_RGBA

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
    absoluteExePath[strlen(absoluteExePath) - strlen("build/")] = '\0';
  #endif
  std::string path = std::string(absoluteExePath);
  return path;
}

typedef struct {
  float x, y;
}point2_t;

typedef struct {
  float x, y, z;
}point3_t;

typedef struct {
  float r, g, b;
}color_t;

typedef uint64_t game_object_id;

typedef uint8_t rgba_t;

struct TextureSegment {
  point2_t lb;
  point2_t lt;
  point2_t rt;
  point2_t rb;

  TextureSegment(point2_t lb = {0., 0.},
                 point2_t lt = {0., 0.},
                 point2_t rt = {0., 0.},
                 point2_t rb = {0., 0.}) noexcept:
    lb(lb),
    lt(lt),
    rt(rt),
    rb(rb)
    { }
};

typedef struct TextureSegment texture_segment_t;

// All classes that are to use callbacks
struct AppInfo {
  void* renderer;
};

inline struct AppInfo fae_app_info;

}  // namespace fae
