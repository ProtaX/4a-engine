#include "Camera.hpp"

#include <functional>

namespace fae {

Camera::Camera(float windowH, float windowW) noexcept {
  view_ = glm::lookAt(
    glm::vec3(-windowW/2, -windowH/2, 1.0f),
    glm::vec3(-windowW/2, -windowH/2, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));
  proj_ = glm::ortho(0.0f, windowW, 0.0f, windowH, 0.0f, 1.0f);
  move_to_ = {};
}

void Camera::MoveCamera(point3_t p) {
  view_ = glm::translate(view_, glm::vec3(p.x, p.y, p.z));
}

void Camera::MoveCamera(const glm::vec3& transVec) {
  view_ = glm::translate(view_, transVec);
}


bool Camera::HandleEvent(const PlayerMoveEvent& e) {
  frames_left_ = e.GetFrames();
  if (!frames_left_)
    return false;

  move_to_ = e.GetMove();
  move_to_.x *= -1. / (static_cast<float>(frames_left_));
  move_to_.y *= -1. / (static_cast<float>(frames_left_));
  move_to_.z *= -1. / (static_cast<float>(frames_left_));

  return true;
}

bool Camera::HandleEvent(const FrameEvent& e) {
  if (frames_left_) {
    MoveCamera(move_to_);
    frames_left_--;
  }
  return true;
}

}  // namespace fae
