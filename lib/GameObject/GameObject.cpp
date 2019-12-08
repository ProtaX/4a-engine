#include "GameObject.hpp"

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

GameObject::GameObject(GameObject&& right) {
    id = right.id;
    p_vertex_buffer = std::move(right.p_vertex_buffer);
    p_vertex_array = std::move(right.p_vertex_array);
    p_vertex_layout = std::move(right.p_vertex_layout);
    p_index_buffer = std::move(right.p_index_buffer);

    m_model_mtx = right.m_model_mtx;
    m_verticies[0] = right.m_verticies[0];
    m_verticies[1] = right.m_verticies[1];
    m_verticies[2] = right.m_verticies[2];
    m_verticies[3] = right.m_verticies[3];
    m_shader_program = right.m_shader_program;
    std::cout << "[Moved] GameObject " << id << std::endl;
}

GameObject::GameObject(const GameObject& right) {
    id = right.id;
    p_vertex_buffer = std::make_unique<VertexBuffer>(m_verticies, sizeof(m_verticies));
    p_vertex_layout = std::make_unique<VertexLayout>();
    p_index_buffer = std::make_unique<IndexBuffer>(m_indicies, sizeof(m_indicies));
    p_vertex_array = std::make_unique<VertexArray>();
    
    SetTextureCoords({1., 1.},
                     {1., 0.},
                     {0., 0.},
                     {0., 1.});

    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(3);
    p_vertex_layout->Push<float>(2);

    p_vertex_array->Bind();
    p_index_buffer->Bind();
    p_vertex_array->AddBuffer(p_vertex_buffer.get(), p_vertex_layout.get());
    p_vertex_array->Unbind();

    m_model_mtx = right.m_model_mtx;
    m_verticies[0] = right.m_verticies[0];
    m_verticies[1] = right.m_verticies[1];
    m_verticies[2] = right.m_verticies[2];
    m_verticies[3] = right.m_verticies[3];
    m_shader_program = right.m_shader_program;
    std::cout << "[Copied] GameObject " << id << std::endl;
}

GameObject& GameObject::operator=(const GameObject& right) {
    id = right.id;
    m_model_mtx = right.m_model_mtx;
    m_verticies[0] = right.m_verticies[0];
    m_verticies[1] = right.m_verticies[1];
    m_verticies[2] = right.m_verticies[2];
    m_verticies[3] = right.m_verticies[3];
    m_shader_program = right.m_shader_program;

    return *this;
}

bool GameObject::operator<(GameObject& right) {
        if ((this->m_verticies[0].coords.z < right.m_verticies[0].coords.z) &&
            (this->m_verticies[1].coords.z < right.m_verticies[1].coords.z) &&
            (this->m_verticies[2].coords.z < right.m_verticies[2].coords.z) &&
            (this->m_verticies[3].coords.z < right.m_verticies[3].coords.z))
            {
                return true;
            }
        return false;
    }

void GameObject::Scale(float percent) {
    m_model_mtx.scale = glm::scale(m_model_mtx.scale, glm::vec3(percent, percent, percent));
}

void GameObject::Scale(point3_t percent) {
    m_model_mtx.scale = glm::scale(m_model_mtx.scale, glm::vec3(percent.x, percent.y, percent.z));
}

void GameObject::Move(point3_t value) {
    m_model_mtx.translation = glm::translate(m_model_mtx.translation, glm::vec3(value.x, value.y, value.z));
}

void GameObject::MoveTo(point3_t value) {
    //m_model_mtx.translation = glm::translate(m_model_mtx.translation, glm::vec3(value.x, value.y, value.z));
}

GameObject::~GameObject() {
        if (!p_index_buffer &&
            !p_vertex_array &&
            !p_vertex_buffer &&
            !p_vertex_layout)
            std::cout << "[~] Empty GameObject " << id << std::endl;
        else std::cout << "[~] GameObject " << id << std::endl;
    }

}