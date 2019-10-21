#pragma once

#include "glew.h"
#include <vector>
#include "Renderer.hpp"

struct VertexBufferAttributes {
    //Тип аттрибута
    GLuint attribType;
    //Количество данных в аттрибуте
    GLint attribCount;
    //Нужно ли нормализировать
    unsigned char isNormalized;
};

class VertexLayout {
private:
    unsigned int stride;
    std::vector<struct VertexBufferAttributes> attributes;

public:
    VertexLayout(unsigned int stride) : stride (stride) { };

    ~VertexLayout();

    template<typename T>
    void Push(GLint count);

    inline unsigned int GetStride() { return stride; };

    inline std::vector<struct VertexBufferAttributes>& GetAttributes() { return attributes; };

    inline unsigned int GetAttribSize(GLuint attribType) {
        switch (attribType)
        {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
        }
        return 0;
    }
};