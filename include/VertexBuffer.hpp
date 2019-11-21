#pragma once

#include "Core.hpp"

namespace fae {

class VertexBuffer {
    GLuint id;
    unsigned int m_stored_data_size;
public:
    VertexBuffer(const void* data, unsigned int size);

    ~VertexBuffer();

    void Bind();

    void Unbind();

    void ReloadData(const void* data);
};

}