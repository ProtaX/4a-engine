#pragma once

#include <stdint.h>

#include <memory>
#include <utility>

#include "DynamicGameObject.hpp"

namespace fae {

class AnimatedGameObject : public DynamicGameObject {
 public:
  AnimatedGameObject() noexcept {
    std::cout << "[->]\tAnimatedGameObject" << std::endl;
    segment_to_draw_ = 0;
  }

  bool HandleEvent(const FrameEvent& e) final;

  virtual ~AnimatedGameObject() {}

 private:
  uint32_t segment_to_draw_;
};

typedef std::shared_ptr<AnimatedGameObject> AnimatedGameObject_p;

template <typename... _Args>
AnimatedGameObject_p CreateAnimatedGameObject(_Args &&... __args) {
  return std::make_shared<AnimatedGameObject>(std::forward<_Args>(__args)...);
}

}  // namespace fae
