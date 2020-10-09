#include <memory>

#include "VertexArray.hpp"

namespace fae {

VertexArray::VertexArray() {
  GLCall(glGenVertexArrays(1, &id_));
  GLCall(glBindVertexArray(id_));
}

void VertexArray::AddBuffer(const std::unique_ptr<VertexBuffer>& buffer, const std::unique_ptr<VertexLayout>& layout) {
  buffer->Bind();
  const auto& attributes = layout->GetAttributes();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < attributes.size(); ++i) {
    const auto& attribute = attributes[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i, attribute.attribCount,
                                    attribute.attribType,
                                    attribute.isNormalized,
                                    layout->GetStride(),
                                    reinterpret_cast<GLvoid*>(offset)));
    offset += attribute.attribCount * layout->GetAttribSize(attribute.attribType);
  }
}

void VertexArray::Bind() const {
  GLCall(glBindVertexArray(id_));
}

void VertexArray::Unbind() const {
  GLCall(glBindVertexArray(0));
}

VertexArray::~VertexArray() {
  std::cout << "[~] VertexArray " << id_ << std::endl;
  GLCall(glDeleteVertexArrays(1, &id_));
}

}  // namespace fae
