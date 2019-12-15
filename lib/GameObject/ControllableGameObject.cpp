#include "ControllableGameObject.hpp"

namespace fae {

bool ControllableGameObject::OnFrame(FrameEvent& e) {
    /* TODO: сделать логику здесь
    if (! (e.GetFramesDrawn() % frames_until_next_segment)) {
        AnimatedTexture* tex = dynamic_cast<AnimatedTexture*>(p_texture.get());
        texture_segment_t seg = tex->GetNextSegment(segment_to_draw++);
        SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
        segment_to_draw = segment_to_draw % tex->GetSegmentCount();
    }
    return true;
    */
   return true;
}

void ControllableGameObject::OnEvent(Event& e) {
    EventDispatcher disp(e);

    disp.Dispatch<KeyPressedEvent>(std::bind(&OnKeyPressed, this, std::placeholders::_1));
    disp.Dispatch<FrameEvent>(std::bind(&OnFrame, this, std::placeholders::_1));
}

bool ControllableGameObject::OnKeyPressed(KeyPressedEvent& e) {
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

}