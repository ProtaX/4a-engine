#include "StaticGameObject.hpp"

namespace fae {
    
void StaticGameObject::OnEvent(Event& e) {
    EventDispatcher disp(e);

    disp.Dispatch<KeyPressedEvent>(std::bind(&OnKeyPressed, this, std::placeholders::_1));
}

bool StaticGameObject::OnKeyPressed(KeyPressedEvent& e) {
    int keycode = e.GetKeyCode();

    if (keycode == GLFW_KEY_W) {
        Move({0., 5.});
    }
    else if (keycode == GLFW_KEY_A) {
        Move({-5.});
    }
    else if (keycode == GLFW_KEY_S) {
        Move({0., -5.});
    }
    else if (keycode == GLFW_KEY_D) {
        Move({5.});
    }
    else return false;
    return true;
}

void StaticGameObject::SetTexture(std::shared_ptr<Texture> texture) {
    p_texture = texture;
    GameObject::SetCoords({-texture->GetW()/2.f, -texture->GetH()/2.f}, {texture->GetW()/2.f, texture->GetH()/2.f});
}

void StaticGameObject::SetCoords(point3_t lb) {
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

void StaticGameObject::UseShaderProgram() {
    GLCall(glUseProgram(m_shader_program));
    GLint model_mtx_loc = GLCall(glGetUniformLocation(m_shader_program, "model"));
    GLint texture_loc = GLCall(glGetUniformLocation(m_shader_program, "Texture"));
    GLCall(glUniformMatrix4fv(model_mtx_loc, 1, GL_FALSE, glm::value_ptr(m_model_mtx.GetModelMtx())));
    GLCall(glUniform1i(texture_loc, p_texture->GetTargetN()));
}

}