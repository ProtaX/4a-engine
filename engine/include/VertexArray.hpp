#pragma once

#include <memory>

#include "Core.hpp"
#include "VertexLayout.hpp"
#include "VertexBuffer.hpp"

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
