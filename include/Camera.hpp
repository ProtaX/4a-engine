#pragma once

#include <memory>
#include <utility>

#include "Core.hpp"
#include "Event.hpp"

namespace fae {

class Camera: public IEventListener {
 public:
  Camera(float windowH, float windowW) noexcept;
  ~Camera() {
    std::cout << "[~] Camera " << std::endl;
  }

  void MoveCamera(point3_t p);

  void MoveCamera(const glm::vec3& transVec);

  bool HandleEvent(const PlayerMoveEvent& e) final;
  bool HandleEvent(const FrameEvent& e) final;

  [[nodiscard]] glm::mat4 GetProj() const { return proj_; }

  [[nodiscard]] glm::mat4 GetVeiw() const { return view_; }

  [[nodiscard]] glm::mat4 GetProjView() const { return proj_ * view_; }

 private:
  uint32_t h_, w_;
  uint32_t h_border_, w_border_;
  uint32_t frames_left_;

  glm::mat4 proj_;
  glm::mat4 view_;
  point3_t move_to_;
};

typedef std::shared_ptr<Camera> Camera_p;

template<typename... _Args>
Camera_p CreateCamera(_Args&&... __args) {
  return std::make_shared<Camera>(std::forward<_Args>(__args)...);
}

}  // namespace fae
