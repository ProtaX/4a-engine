#pragma once

#include <memory>
#include <utility>

#include "DynamicGameObject.hpp"
#include "Event.hpp"

namespace fae {

class ControllableGameObject: public DynamicGameObject, IListenable {
 public:
  ControllableGameObject() {
    std::cout << "[->]\tControllableGameObject" << std::endl;
    segment_to_draw_ = 0u;
    speed_ = 10.0f;
    frames_before_idle_ = 10u;
  }

  virtual ~ControllableGameObject() { }

  void SetLeftAnimation(AnimatedTexture_p left) { p_texture_left_ = left; }

  void SetRightAnimation(AnimatedTexture_p right) { p_texture_right = right; }

  void SetUpAnimation(AnimatedTexture_p up) { p_texture_up_ = up; }

  void SetDownAnimation(AnimatedTexture_p down) { p_texture_down = down; }

  void SetIdleAnimation(AnimatedTexture_p idle) { p_texture_idle_ = idle;
                                                          SetTexture(idle); }

  void SetSpeed(float speed) { speed_ = speed; }

  bool HandleEvent(const FrameEvent& e) final;
  bool HandleEvent(const KeyPressedEvent& e) final;

  void AddEventListener(EventType t, std::shared_ptr<IEventListener> object) final;

 private:
  int last_key_pressed_;
  uint32_t segment_to_draw_;
  uint32_t frames_before_idle_;
  bool is_animation_started_;
  float speed_;
  point3_t per_frame_move_;
  std::shared_ptr<AnimatedTexture> p_texture_left_;
  std::shared_ptr<AnimatedTexture> p_texture_right;
  std::shared_ptr<AnimatedTexture> p_texture_up_;
  std::shared_ptr<AnimatedTexture> p_texture_down;
  std::shared_ptr<AnimatedTexture> p_texture_idle_;
  std::shared_ptr<AnimatedTexture> next_frame_anim_;
  // p_texture is current animation playing

  void PlayAnimation(std::shared_ptr<AnimatedTexture> anim) {
    if (is_animation_started_ && (texture_ == anim))
      return;
    next_frame_anim_ = anim;
    is_animation_started_ = true;
  }
};

typedef std::shared_ptr<ControllableGameObject> ControllableGameObject_p;

template<typename... _Args>
ControllableGameObject_p CreateControllableGameObject(_Args&&... __args) {
  return std::make_shared<ControllableGameObject>(std::forward<_Args>(__args)...);
}

}  // namespace fae
