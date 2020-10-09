#include <stdint.h>

#include "VertexBuffer.hpp"

namespace fae {

VertexBuffer::VertexBuffer(const void* data, size_t size) {
  stored_data_size_ = size;
  GLCall(glGenBuffers(1, &id_));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &id_));
  std::cout << "[~] VertexBuffer " << id_ << std::endl;
}

void VertexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
}

void VertexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::ReloadData(const void* data) {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
  GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, stored_data_size_, data));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

}  // namespace fae
