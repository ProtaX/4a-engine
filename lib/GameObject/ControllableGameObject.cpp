#include "ControllableGameObject.hpp"

namespace fae {

bool ControllableGameObject::OnFrame(FrameEvent& e) {
    if (!(e.GetFramesDrawn() % (e.GetFps() / p_texture->GetFps())) && animation_started) {
        if (!p_texture) {
            std::cout << "ControllableGameObject::OnFrame::Error: texture is nt set" << std::endl;
            return false;
        }
        if (next_frame_anim) {
            SetTexture(next_frame_anim);
            segment_to_draw = 0;
            next_frame_anim = nullptr;
        }
        texture_segment_t seg = p_texture->GetNextSegment(segment_to_draw++);
        SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
        segment_to_draw = segment_to_draw % p_texture->GetSegmentCount();
        Move(per_frame_move);
        PlayerMoveEvent move_event(per_frame_move, (e.GetFps() / p_texture->GetFps() - 1));
        for (auto& cb: m_move_callbacks)
            cb(move_event);
        if (segment_to_draw == 0)
            animation_started = false;
        frames_before_idle = p_texture->GetFps();
    }
    
    //Handle idle
    if (!animation_started) {
        if (frames_before_idle)
            frames_before_idle--;
        else {
            per_frame_move = {};
            animation_started = true;
            PlayAnimation(p_texture_idle);
            frames_before_idle = p_texture->GetFps();
        }
    }
    
    return true;
}

void ControllableGameObject::OnEvent(Event& e) {
    EventDispatcher disp(e);

    disp.Dispatch<KeyPressedEvent>(std::bind(&OnKeyPressed, this, std::placeholders::_1));
    disp.Dispatch<FrameEvent>(std::bind(&OnFrame, this, std::placeholders::_1));
}

bool ControllableGameObject::OnKeyPressed(KeyPressedEvent& e) {
    int keycode = e.GetKeyCode();
    m_last_key_pressed = keycode;
    switch (keycode) {
        case GLFW_KEY_W:
            per_frame_move = {0., m_speed, 0.};
            PlayAnimation(p_texture_up);
            break;
        case GLFW_KEY_A:
            per_frame_move = {-m_speed, 0., 0.};
            PlayAnimation(p_texture_left);
            break;
        case GLFW_KEY_S:
            per_frame_move = {0., -m_speed, 0.};
            PlayAnimation(p_texture_down);
            break;
        case GLFW_KEY_D:
            per_frame_move = {m_speed, 0., 0.};
            PlayAnimation(p_texture_right);
            break;
    }
    return true;
}

void ControllableGameObject::AddMoveListener(std::shared_ptr<IEventListener> object) {
    if (!object) {
       std::cout << "Renderer::AddMoveListener::Error: got null object" << std::endl;
       return;
    }
    std::function<void(Event&)> f = std::bind(&IEventListener::OnEvent, object.get(), std::placeholders::_1);
    m_move_callbacks.push_back(f);
}

}