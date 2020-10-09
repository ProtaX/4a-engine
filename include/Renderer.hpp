#pragma once

#include <stdint.h>

#include <list>
#include <string>
#include <memory>
#include <utility>

#include "Core.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "GameScene.hpp"
#include "Texture.hpp"
#include "Event.hpp"

namespace fae {

class Renderer: public IListenable, public IEventListener {
 public:
  Renderer(int window_h, int window_w, std::string name, bool init_window = true) noexcept;

  void InitWindow();

  void Start();

  void SetScene(std::shared_ptr<GameScene> scene) { this->scene_ = scene; }

  void SetFps(uint32_t fps) { this->fps_ = fps; }

  void SetIcon(Texture_p icon) const;

  void AddEventListener(EventType t, std::shared_ptr<IEventListener> object) final;

  bool HandleEvent(const KeyPressedEvent& e) final;

  ~Renderer();

 private:
  float window_h_, window_w_;
  int glwf_context_v_mj_, glwf_context_v_mn_;
  int glfw_opengl_profile_;
  int glfw_resizable_;
  uint32_t fps_;
  double frame_time_;
  GLboolean glew_experimantal_;
  GLenum glBlend_sfactor_, glBlend_dfactor_;
  GLFWwindow* window_;
  std::string window_name_;

  std::shared_ptr<GameScene> scene_;

  void OnFrame(int frames_drawn);
};

typedef std::unique_ptr<Renderer> Renderer_p;

template<typename... _Args>
Renderer_p CreateRenderer(_Args&&... __args) {
  return std::make_unique<Renderer>(std::forward<_Args>(__args)...);
}

}  // namespace fae
