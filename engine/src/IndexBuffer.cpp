#include "IndexBuffer.hpp"

#include "FAEUtils.h"

namespace fae {

IndexBuffer::IndexBuffer(const void* data, GLsizeiptr size) noexcept {
  glGenBuffers(1, &id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
  std::cout << "[~] IndexBuffer " << id_ << std::endl;
  glDeleteBuffers(1, &id_);
}

}  // namespace fae
