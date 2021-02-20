#include "ControllableGameObject.hpp"

#include "GLFW/glfw3.h"

namespace fae {

bool ControllableGameObject::HandleEvent(const FrameEvent& e) {
  if (!(e.GetFramesDrawn() % (e.GetFps() / texture_->GetFps())) && is_animation_started_) {  // TODO: division by zero here
    if (!texture_) {
      std::cout << "ControllableGameObject::OnFrame::Error: texture is nt set" << std::endl;
      return false;
    }

    if (next_frame_anim_) {
      SetTexture(next_frame_anim_);
      segment_to_draw_ = 0;
      next_frame_anim_ = nullptr;
    }

    texture_segment_t seg = texture_->GetNextSegment(segment_to_draw_++);
    SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
    segment_to_draw_ = segment_to_draw_ % texture_->GetSegmentCount();
    Move(per_frame_move_);
    PlayerMoveEvent move_event(per_frame_move_, (e.GetFps() / texture_->GetFps() - 1));

    auto& cbs = GetCallbacks(EventType::PlayerMove);
    for (auto& cb : cbs)
      cb(move_event);
    if (segment_to_draw_ == 0)
      is_animation_started_ = false;
    frames_before_idle_ = texture_->GetFps();
  }

  /* Handle idle */
  if (!is_animation_started_) {
    if (frames_before_idle_) {
      frames_before_idle_--;
    } else {
      per_frame_move_ = {};
      is_animation_started_ = true;
      PlayAnimation(p_texture_idle_);
      frames_before_idle_ = texture_->GetFps();
    }
  }

  return true;
}

bool ControllableGameObject::HandleEvent(const KeyPressedEvent& e) {
  int keycode = e.GetKeyCode();
  last_key_pressed_ = keycode;
  switch (keycode) {
    case GLFW_KEY_W:
      per_frame_move_ = {0., speed_, 0.};
      PlayAnimation(p_texture_up_);
      break;
    case GLFW_KEY_A:
      per_frame_move_ = {-speed_, 0., 0.};
      PlayAnimation(p_texture_left_);
      break;
    case GLFW_KEY_S:
      per_frame_move_ = {0., -speed_, 0.};
      PlayAnimation(p_texture_down);
      break;
    case GLFW_KEY_D:
      per_frame_move_ = {speed_, 0., 0.};
      PlayAnimation(p_texture_right);
      break;
  }
  return true;
}

void ControllableGameObject::AddEventListener(EventType t, std::shared_ptr<IEventListener> object) {
  if (!object) {
     std::cout << "Renderer::AddMoveListener::Error: got null object" << std::endl;
     return;
  }
  EventCB f = std::bind(&IEventListener::OnEvent, object.get(), std::placeholders::_1);
  AddCallback(t, f);
}

}  // namespace fae
