#pragma once

#include <functional>
#include <memory>
#include <utility>

#include "GameObject.hpp"
#include "Texture.hpp"

namespace fae {

class StaticGameObject: public GameObject {
 public:
  StaticGameObject() noexcept {
    std::cout << "[->]\tStaticGameObject" << std::endl;
  }

  virtual ~StaticGameObject() { }

  bool HandleEvent(const KeyPressedEvent& e) final;

  virtual void ChangeState() { }

  void SetTexture(std::shared_ptr<Texture> texture);

  void SetCoords(point3_t lb);

  void UseShaderProgram();

 protected:
  std::shared_ptr<Texture> p_texture;
};

typedef std::shared_ptr<StaticGameObject> StaticGameObject_p;

template<typename... _Args>
StaticGameObject_p CreateStaticGameObject(_Args&&... __args) {
  return std::make_shared<StaticGameObject>(std::forward<_Args>(__args)...);
}

}  // namespace fae
