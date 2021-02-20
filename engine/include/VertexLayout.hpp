#pragma once

#include <stdint.h>

#include <vector>

#include "Core.hpp"

namespace fae {

struct VertexBufferAttributes {
  GLuint attribType;
  GLint attribCount;
  uint8_t isNormalized;
};

class VertexLayout {
 public:
  explicit VertexLayout(uint32_t stride = 0) noexcept: stride(stride) { }

  ~VertexLayout();

  template<typename T>
  void Push(GLint count);

  [[nodiscard]] uint32_t GetStride() const { return stride; }

  [[nodiscard]] std::vector<struct VertexBufferAttributes>& GetAttributes() { return attributes; }

  [[nodiscard]] static size_t GetAttribSize(GLuint attribType) {
    switch (attribType) {
      case GL_FLOAT:          return sizeof(GLfloat);
      case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
      case GL_UNSIGNED_INT:   return sizeof(GLuint);
    }
    return 0u;
  }

 private:
  uint32_t stride;
  std::vector<struct VertexBufferAttributes> attributes;
};

}  // namespace fae
