#pragma once

#include "Core.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Event.hpp"

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
    GLuint target;
    unsigned int h;
    unsigned int w;
    unsigned char* p_image_data;

    GameTexture2D() {
        id = 0;
        target = 0;
        h = 0;
        w = 0;
        p_image_data = nullptr;
    }
};

typedef struct GameVertex vertex_t;
typedef struct GameTexture2D texture_t;

class GameObject {
private:
    //Destructs on ~GameObject()
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

    bool OnKeyPressed(KeyPressedEvent& e);
    
public:
    game_object_id id;
    //Sets up default vertex buffer layout, texture coords, 
    //creates VAO and VBO, uses default IBO
    GameObject();

    GameObject(GameObject&& right);

    void SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt);

    void SetCoords(point3_t rt, point3_t rb, point3_t lb, point3_t lt);

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

    inline int GetShaderProgram() const { return this->m_shader_program; }

    inline float GetLayer();

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

    GameObject& operator=(const GameObject& right) = default;
    /*{
        this->p_index_buffer = right.p_index_buffer;
        this->p_vertex_array = right.p_vertex_array;
        this->p_vertex_buffer = right.p_vertex_buffer;
        this->p_vertex_layout = right.p_vertex_layout;

        this->
    }*/

    //TODO: функции взаимодействия с матрицей модели

    void OnEvent(Event& e);

    virtual ~GameObject() {
        if (!p_index_buffer &&
            !p_vertex_array &&
            !p_vertex_buffer &&
            !p_vertex_layout)
            std::cout << "[~] Empty GameObject " << id << std::endl;
        else std::cout << "[~] GameObject " << id << std::endl;
    }
};

}