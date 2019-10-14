#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
     glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Unbind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}