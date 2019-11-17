#pragma once

#include "Core.hpp"
#include "VertexLayout.hpp"
#include "VertexBuffer.hpp"
#include <vector>

namespace fae {

class VertexArray {
private:
    GLuint id;

public:
    VertexArray();

    ~VertexArray();

    void AddBuffer(VertexBuffer& buffer, VertexLayout& layout);

    void AddBuffer(VertexBuffer* buffer, VertexLayout* layout);

    void Bind() const;

    void Unbind() const;
};

}