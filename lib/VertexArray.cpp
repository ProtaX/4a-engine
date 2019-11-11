#include "VertexArray.hpp"

namespace fae {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

void VertexArray::AddBuffer(VertexBuffer& buffer, VertexLayout& layout) {
    buffer.Bind();
    const auto& attributes = layout.GetAttributes();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        const auto& attribute = attributes[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, attribute.attribCount, attribute.attribType, attribute.isNormalized, layout.GetStride(), (GLvoid*)offset));
        offset += attribute.attribCount * layout.GetAttribSize(attribute.attribType);
    }
}

void VertexArray::AddBuffer(VertexBuffer* buffer, VertexLayout* layout) {
    buffer->Bind();
    const auto& attributes = layout->GetAttributes();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        const auto& attribute = attributes[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, attribute.attribCount, attribute.attribType, attribute.isNormalized, layout->GetStride(), (GLvoid*)offset));
        offset += attribute.attribCount * layout->GetAttribSize(attribute.attribType);
    }
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(id));
}

void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}

VertexArray::~VertexArray() {

}

}