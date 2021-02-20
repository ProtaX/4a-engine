#pragma once

#include <memory>

#include "VertexBuffer.hpp"
#include "VertexLayout.hpp"

#include "GL/glew.h"

namespace fae {

class VertexArray {
 public:
  VertexArray();

  ~VertexArray();

  void AddBuffer(const std::unique_ptr<VertexBuffer>& buffer, const std::unique_ptr<VertexLayout>& layout);

  void Bind() const;

  void Unbind() const;

 private:
  GLuint id_;
};

}  // namespace fae
