#pragma once

#include "Core.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

namespace fae {

struct GameVertex
{
    point3_t coords;
    color_t color;
    point2_t tex_coords;
};

struct GameTexture2D {
    GLuint id;
    unsigned char* p_image_data;
    int target = GL_TEXTURE;
};

typedef struct GameVertex vertex_t;
typedef struct GameTexture2D texture_t;

class GameObject {
private:
    std::unique_ptr<VertexBuffer> p_vertex_buffer;
    std::unique_ptr<VertexArray> p_vertex_array;
    std::unique_ptr<VertexLayout> p_vertex_layout;
    std::unique_ptr<IndexBuffer> p_index_buffer;

    glm::mat4 m_model_mtx;
    vertex_t m_verticies[4];
    texture_t m_texture;
    GLuint m_indicies[6] = {
        0, 1, 3,
        1, 2, 3
    };
    
    int m_shader_program;
    
public:
    //Sets up default vertex buffer layout, texture coords, 
    //creates VAO and VBO, uses default IBO
    GameObject();

    void SetTextureCoords(point2_t lb, point2_t lt, point2_t rt, point2_t rb);

    void SetCoords(point2_t lb, point2_t lt, point2_t rt, point2_t rb);

    void SetCoords(point3_t lb, point3_t lt, point3_t rt, point3_t rb);

    //For rectangles only, z = 0
    void SetCoords(point2_t lb, point2_t rt);

    //For rectangles only, z = lb.z = rt.z
    void SetCoords(point3_t lb, point3_t rt);

    //Take (0, 0) as a lb point
    void SetSize(point2_t rt);

    void SetSingleTexture(unsigned char* pixel_data, int h, int w, int target);

    void SetShaderProgram(int shader) { this->m_shader_program = shader; }

    //TODO: зедсь должно быть использование методов класса шейдера
    void UseShaderProgram();

    inline void BindVertexBuffer() const { this->p_vertex_buffer->Bind(); }

    inline void BindVertexArray() const { this->p_vertex_array->Bind(); }

    inline void BindIndexBuffer() const { this->p_index_buffer->Bind(); }

    inline void UnbindVertexBuffer() const { this->p_vertex_buffer->Unbind(); }

    inline void UnbindVertexArray() const { this->p_vertex_array->Unbind(); }

    inline void UnbindIndexBuffer() const { this->p_index_buffer->Unbind(); }

    inline glm::mat4 GetModelMtx() const { return this->m_model_mtx; }

    //TODO: функции взаимодействия с матрицей модели

    virtual ~GameObject();
};

}