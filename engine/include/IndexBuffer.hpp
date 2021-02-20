#pragma once

#include "Core.hpp"

namespace fae {

class IndexBuffer {
 public:
  IndexBuffer(const void* data, GLsizeiptr size) noexcept;

  ~IndexBuffer();

  void Bind() const;

  void Unbind() const;

 private:
  GLuint id_;
};

}  // namespace fae
