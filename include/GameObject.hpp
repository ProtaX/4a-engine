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

    GameVertex() {
        coords = {0., 0., 0.};
        color = {0., 0., 0.};
        tex_coords = {0., 0.};
    }
};

struct GameTexture2D {
    GLuint id;
    unsigned char* p_image_data;
    GLuint target;

    GameTexture2D() {
        id = 0;
        //Not used
        p_image_data = nullptr;
        target = 0;
    }
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

    GameObject(const GameObject& right);

    void SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt);

    void SetCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt);

    void SetCoords(point3_t rt, point3_t rb, point3_t lb, point3_t lt);

    //For rectangles only, z = 0
    void SetCoords(point2_t lb, point2_t rt);

    //For rectangles only, z = lb.z = rt.z
    void SetCoords(point3_t lb, point3_t rt);

    //Take (0, 0) as a lb point
    void SetSize(point2_t rt);

    void SetLayer(float z);

    void SetSingleTexture(unsigned char* pixel_data, int h, int w, int target = GL_TEXTURE);

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

    inline vertex_t* GetVertexDataPtr() const { return (vertex_t*)m_verticies; }

    float GetLayer();

    bool operator<(GameObject& right) {
        if ((this->m_verticies[0].coords.z < right.m_verticies[0].coords.z) &&
            (this->m_verticies[1].coords.z < right.m_verticies[1].coords.z) &&
            (this->m_verticies[2].coords.z < right.m_verticies[2].coords.z) &&
            (this->m_verticies[3].coords.z < right.m_verticies[3].coords.z))
            {
                return true;
            }
        return false;
    }

    /* Not used
    bool operator==(GameObject& right) {
        int res_v = std::memcmp(m_verticies, right.m_verticies, sizeof(m_verticies));
        int res_t = std::memcmp(&m_texture, &right.m_texture, sizeof(m_texture));
        if (!res_v && !res_t)
            return true;
        return false;
    }
    */

    //TODO: функции взаимодействия с матрицей модели

    virtual ~GameObject() { }

    //Что-то сделать с этим надо
    void Draw();
};

}