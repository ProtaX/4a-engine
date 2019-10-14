#pragma once

#include "glew.h"
#include "Renderer.hpp"

class IndexBuffer {
    GLuint id;

public:
    IndexBuffer(const void* data, unsigned int size);

    ~IndexBuffer();

    void Bind();

    void Unbind();

};