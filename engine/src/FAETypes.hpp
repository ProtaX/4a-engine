#pragma once

#define TEST_BUILD

#include <stdlib.h>
#include <stdint.h>

#include <windows.h>
#include <iostream>
#include <memory>
#include <string>

#include <GL/glew.h>
#include "SOIL.h"

namespace fae {

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

typedef struct TextureSegment texture_segment_t;

// All classes that are to use callbacks
struct AppInfo {
  void* renderer;
};

inline struct AppInfo fae_app_info;

}  // namespace fae
