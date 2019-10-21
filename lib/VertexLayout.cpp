#include "VertexLayout.hpp"

VertexLayout::~VertexLayout() {

}

template<>
void VertexLayout::Push<GLfloat>(GLint count) {
    attributes.push_back({GL_FLOAT, count, GL_FALSE});
    stride += sizeof(GLfloat) * count;
}

template<>
void VertexLayout::Push<GLuint>(GLint count) {
    attributes.push_back({GL_UNSIGNED_INT, count, GL_TRUE});
    stride += sizeof(GLuint) * count;
}

template<>
void VertexLayout::Push<GLubyte>(GLint count) {
    attributes.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride += sizeof(GLubyte) * count;
}