#pragma once

#include "glew.h"
#include "Renderer.hpp"

class VertexBuffer {
    GLuint id;

public:
    VertexBuffer(const void* data, unsigned int size);

    ~VertexBuffer();

    void Bind();

    void Unbind();
};