#pragma once

#include <stdint.h>

#include "GL/glew.h"

namespace fae {

class VertexBuffer {
 public:
  VertexBuffer(const void* data, size_t size);

  ~VertexBuffer();

  void Bind() const;

  void Unbind() const;

  void ReloadData(const void* data);

 private:
  GLuint id_;
  size_t stored_data_size_;
};

}  // namespace fae
