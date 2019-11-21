#include "VertexBuffer.hpp"

namespace fae {

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    m_stored_data_size = size;
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::ReloadData(const void* data) {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_stored_data_size, data));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

}