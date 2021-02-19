#include "VertexArray.hpp"

namespace fae {

VertexArray::VertexArray() {}

VertexArray::~VertexArray() {}

void VertexArray::Bind() const {}

void VertexArray::Unbind() const {}

void VertexArray::AddBuffer(const std::unique_ptr<VertexBuffer> &buffer, const std::unique_ptr<VertexLayout> &layout) {}

}
