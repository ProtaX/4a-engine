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

void GameObject::SetSingleTexture(unsigned char* pixel_data, int h, int w, int target) {
    float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    m_texture.target = target;
    GLCall(glGenTextures(1, &(m_texture.id)));
    GLCall(glActiveTexture(m_texture.target));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture.id));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, h, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data));
    GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
}

void GameObject::UseShaderProgram() {
    GLCall(glUseProgram(m_shader_program));
    //TODO: эти вызовы должны быть частью класса шейдера
    GLint texture_loc = GLCall(glGetUniformLocation(m_shader_program, "ourTexture"));
    GLint transform_loc = GLCall(glGetUniformLocation(m_shader_program, "is_transformable"));
    GLCall(glUniform1i(transform_loc, 0));
    GLCall(glUniform1i(texture_loc, m_texture.target - GL_TEXTURE0 ));
}

GameObject::GameObject() {
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
}

float GameObject::GetLayer() {
    if (m_verticies[0].coords.z == 
        m_verticies[1].coords.z == 
        m_verticies[2].coords.z ==
        m_verticies[3].coords.z) {
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
    if (keycode == GLFW_KEY_A) {
        std::cout << "'A' key pressed\n";
        m_verticies[0].coords.y--;
        m_verticies[1].coords.y--;
        m_verticies[2].coords.y--;
        m_verticies[3].coords.y--;
    }
    if (p_vertex_buffer)
        p_vertex_buffer->ReloadData(m_verticies);
    else return false;
    return true;
}

GameObject::GameObject(GameObject&& right) {
    p_vertex_buffer = std::move(right.p_vertex_buffer);
    p_vertex_array = std::move(right.p_vertex_array);
    p_vertex_layout = std::move(right.p_vertex_layout);
    p_index_buffer = std::move(right.p_index_buffer);

    m_model_mtx = right.m_model_mtx;
    m_verticies[0] = right.m_verticies[0];
    m_verticies[1] = right.m_verticies[1];
    m_verticies[2] = right.m_verticies[2];
    m_verticies[3] = right.m_verticies[3];
    m_texture = right.m_texture;
    m_shader_program = right.m_shader_program;
}

}