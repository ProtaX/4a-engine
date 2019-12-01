#include "GameObject.hpp"
#include <functional>

namespace fae {

void GameObject::SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt) {
    m_verticies[0].tex_coords = rt;
    m_verticies[1].tex_coords = rb;
    m_verticies[2].tex_coords = lb;
    m_verticies[3].tex_coords = lt;
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetCoords(point3_t lb, point3_t lt, point3_t rt, point3_t rb) {
    m_verticies[0].coords = rt;
    m_verticies[1].coords = rb;
    m_verticies[2].coords = lb;
    m_verticies[3].coords = lt;
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetCoords(point3_t lb, point3_t rt) {
    if (lb.z != rt.z) {
        std::cout << "GameObject::SetCoords::Error: Bad z coordinate" << std::endl;
        return;
    }
    m_verticies[0].coords = {rt.x, rt.y, lb.z};
    m_verticies[1].coords = {rt.x, lb.y, lb.z};
    m_verticies[2].coords = {lb.x, lb.y, lb.z};
    m_verticies[3].coords = {lb.x, rt.y, lb.z};
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetCoords(point3_t lb) {
    if (!p_texture) {
        std::cout << "GameObject::SetCoords::Error: texture is not set" << std::endl;
        return;
    }

    //rt.x -> lb.x + p_texture->GetH()
    //rt.y -> lb.y + p_texture->GetW()
    m_verticies[0].coords = {lb.x + p_texture->GetH(), lb.y + p_texture->GetW(),   lb.z};
    m_verticies[1].coords = {lb.x + p_texture->GetH(), lb.y,                       lb.z};
    m_verticies[2].coords = {lb.x,                     lb.y,                       lb.z};
    m_verticies[3].coords = {lb.x,                     lb.y + p_texture->GetW(),   lb.z};
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetSize(point2_t rt) {
    m_verticies[0].coords = {rt.x, rt.y, 0.};
    m_verticies[1].coords = {rt.x, 0.,   0.};
    m_verticies[2].coords = {0.,   0.,   0.};
    m_verticies[3].coords = {0.,   rt.y, 0.};
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetLayer(float z) {
    m_verticies[0].coords.z = z;
    m_verticies[1].coords.z = z;
    m_verticies[2].coords.z = z;
    m_verticies[3].coords.z = z;
    if (!p_vertex_buffer) {
        std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
        return;
    }
    p_vertex_buffer->ReloadData(m_verticies);
}

void GameObject::SetTexture(std::shared_ptr<Texture> texture) {
    p_texture = texture;
}

void GameObject::UseShaderProgram() {
    GLCall(glUseProgram(m_shader_program));
    GLint model_mtx_loc = GLCall(glGetUniformLocation(m_shader_program, "model"));
    GLint texture_loc = GLCall(glGetUniformLocation(m_shader_program, "Texture"));
    GLCall(glUniformMatrix4fv(model_mtx_loc, 1, GL_FALSE, glm::value_ptr(m_model_mtx)));
    GLCall(glUniform1i(texture_loc, p_texture->GetTargetN()));
}

GameObject::GameObject() {
    id = (game_object_id)this;
    p_vertex_buffer = std::make_unique<VertexBuffer>(m_verticies, sizeof(m_verticies));
    p_vertex_layout = std::make_unique<VertexLayout>();
    p_index_buffer = std::make_unique<IndexBuffer>(m_indicies, sizeof(m_indicies));
    p_vertex_array = std::make_unique<VertexArray>();
    
    SetTextureCoords({1., 1.},
                     {1., 0.},
                     {0., 0.},
                     {0., 1.});
                     
    m_model_mtx = glm::mat4(1.0f);

    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(2);

    p_vertex_array->Bind();
    p_index_buffer->Bind();
    p_vertex_array->AddBuffer(p_vertex_buffer.get(), p_vertex_layout.get());
    p_vertex_array->Unbind();

    std::cout << "[Created] GameObject " << id << std::endl;
}

float GameObject::GetLayer() {
    if ((m_verticies[0].coords.z == m_verticies[1].coords.z) && 
        (m_verticies[2].coords.z == m_verticies[3].coords.z) &&
        (m_verticies[1].coords.z == m_verticies[2].coords.z)) {
            return m_verticies[0].coords.z;
        }
    else return -1.0f;
}

void GameObject::OnEvent(Event& e) {
    EventDispatcher disp(e);
    
    disp.Dispatch<KeyPressedEvent>(std::bind(&OnKeyPressed, this, std::placeholders::_1));
}

bool GameObject::OnKeyPressed(KeyPressedEvent& e) {
    int keycode = e.GetKeyCode();
    //TODO: заменить на изменение матрицы модели
    glm::vec3 heroMove = glm::vec3(0.0f); 
    if (keycode == GLFW_KEY_W) {
        std::cout << "[Going upwards]" << id << std::endl;
    }
    else if (keycode == GLFW_KEY_A) {
        heroMove[0] = -(double)p_texture->GetH() / 6.;
    }
    else if (keycode == GLFW_KEY_S) {
        std::cout << "[Going downwards]" << id << std::endl;
    }
    else if (keycode == GLFW_KEY_D) {
        heroMove[0] = (double)p_texture->GetH() / 6.;
    }
    else return false;
    m_model_mtx = glm::translate(m_model_mtx, heroMove);
    return true;
}

GameObject::GameObject(GameObject&& right) {
    id = (game_object_id)this;
    p_vertex_buffer = std::move(right.p_vertex_buffer);
    p_vertex_array = std::move(right.p_vertex_array);
    p_vertex_layout = std::move(right.p_vertex_layout);
    p_index_buffer = std::move(right.p_index_buffer);
    p_texture = right.p_texture;

    m_model_mtx = right.m_model_mtx;
    m_verticies[0] = right.m_verticies[0];
    m_verticies[1] = right.m_verticies[1];
    m_verticies[2] = right.m_verticies[2];
    m_verticies[3] = right.m_verticies[3];
    m_shader_program = right.m_shader_program;
    std::cout << "[Moved] GameObject " << id << std::endl;
}

}