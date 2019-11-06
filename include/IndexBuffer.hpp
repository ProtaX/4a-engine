#pragma once

#include "Renderer.hpp"

namespace fae {

class IndexBuffer {
    GLuint id;

public:
    IndexBuffer(const void* data, unsigned int size);

    ~IndexBuffer();

    void Bind();

    void Unbind();

};

}