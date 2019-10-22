#pragma once

#include "glew.h"
#include "VertexLayout.hpp"
#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include <vector>

namespace fae {

class VertexArray {
private:
    GLuint id;

public:
    VertexArray();

    ~VertexArray();

    void AddBuffer(VertexBuffer& buffer, VertexLayout& layout);

    void Bind() const;

    void Unbind() const;
};

}