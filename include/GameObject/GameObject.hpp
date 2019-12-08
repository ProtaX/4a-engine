#pragma once

#include "Core.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Event.hpp"
#include "IControlable.hpp"

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

struct ModelMtx {
    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scale;

    ModelMtx() {
        translation = glm::mat4(1.0f);
        rotation = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
    }

    inline glm::mat4 GetModelMtx() const {
        return translation * rotation * scale;
    }
};

typedef struct GameVertex vertex_t;

class GameObject: public IKeyControlable {
protected:
    game_object_id id;
    //Destructs on ~GameObject()
    std::unique_ptr<VertexBuffer> p_vertex_buffer;
    std::unique_ptr<VertexArray> p_vertex_array;
    std::unique_ptr<VertexLayout> p_vertex_layout;
    std::unique_ptr<IndexBuffer> p_index_buffer;

    ModelMtx m_model_mtx;
    vertex_t m_verticies[4];
    GLuint m_indicies[6] = {
        0, 1, 3,
        1, 2, 3
    };

    int m_shader_program;

    virtual bool OnKeyPressed(KeyPressedEvent& e) = 0;
    
public:
    //Sets up default vertex buffer layout, texture coords, 
    //creates VAO and VBO, uses default IBO
    GameObject();

    GameObject(GameObject&& right);

    GameObject(const GameObject& right);

    //Copies ONLY not unique data
    GameObject& operator=(const GameObject&);

    bool operator<(GameObject& right);

    void SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt);

    void SetCoords(point3_t rt, point3_t rb, point3_t lb, point3_t lt);

    void SetCoords(point3_t lb, point3_t rt);

    //Take (0, 0) as a lb point
    void SetSize(point2_t rt);

    void SetLayer(float z);

    void SetShaderProgram(int shader) { this->m_shader_program = shader; }

    float GetLayer();

    void Scale(float percent);

    void Scale(point3_t percent);

    void Move(point3_t value);

    void MoveTo(point3_t value);

    //Set left-bottom point only if p_texture is set
    void SetCoords(point3_t lb);

    inline void BindVertexBuffer() const { this->p_vertex_buffer->Bind(); }

    inline void BindVertexArray() const { this->p_vertex_array->Bind(); }

    inline void BindIndexBuffer() const { this->p_index_buffer->Bind(); }

    inline void UnbindVertexBuffer() const { this->p_vertex_buffer->Unbind(); }

    inline void UnbindVertexArray() const { this->p_vertex_array->Unbind(); }

    inline void UnbindIndexBuffer() const { this->p_index_buffer->Unbind(); }

    inline glm::mat4 GetModelMtx() const { return this->m_model_mtx.GetModelMtx(); }

    inline vertex_t* GetVertexDataPtr() const { return (vertex_t*)m_verticies; }

    inline int GetShaderProgram() const { return this->m_shader_program; }

    inline game_object_id GetId() const { return id; }

    virtual void ChangeState() = 0;

    virtual void OnEvent(Event& e) = 0;

    virtual void UseShaderProgram() = 0;

    virtual ~GameObject();
};

}