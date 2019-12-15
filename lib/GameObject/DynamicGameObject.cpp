#include "DynamicGameObject.hpp"

namespace fae {
    
void DynamicGameObject::SetTexture(std::shared_ptr<AnimatedTexture> texture) {
    p_texture = texture;
    texture_segment_t seg = texture->GetSegment(0,0);
    SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
    GameObject::SetCoords({-texture->GetSegmentW()/2.f, -texture->GetSegmentH()/2.f}, 
            {texture->GetSegmentW()/2.f, texture->GetSegmentH()/2.f});
    SetLength(texture->GetSegmentCount());
}

bool DynamicGameObject::OnFrame(FrameEvent& e) {
    if (! (e.GetFramesDrawn() % frames_until_next_segment)) {
        AnimatedTexture* tex = dynamic_cast<AnimatedTexture*>(p_texture.get());
        texture_segment_t seg = tex->GetNextSegment(segment_to_draw++);
        SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
        segment_to_draw = segment_to_draw % tex->GetSegmentCount();
    }
    return true;
}

void DynamicGameObject::UseShaderProgram() {
    GLCall(glUseProgram(m_shader_program));
    GLint model_mtx_loc = GLCall(glGetUniformLocation(m_shader_program, "model"));
    GLint texture_loc = GLCall(glGetUniformLocation(m_shader_program, "Texture"));
    GLCall(glUniformMatrix4fv(model_mtx_loc, 1, GL_FALSE, glm::value_ptr(m_model_mtx.GetModelMtx())));
    GLCall(glUniform1i(texture_loc, p_texture->GetTargetN()));
}

void DynamicGameObject::SetCoords(point3_t lb) {
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

void DynamicGameObject::OnEvent(Event& e) {
    EventDispatcher disp(e);

    disp.Dispatch<KeyPressedEvent>(std::bind(&OnKeyPressed, this, std::placeholders::_1));
    disp.Dispatch<FrameEvent>(std::bind(&OnFrame, this, std::placeholders::_1));
}

bool DynamicGameObject::OnKeyPressed(KeyPressedEvent& e) {
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

void DynamicGameObject::SetLength(int frames) {
    frames_until_next_segment = frames;
}

}