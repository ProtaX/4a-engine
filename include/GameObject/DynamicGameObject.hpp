#pragma once

#include <functional>
#include <memory>

#include "GameObject.hpp"
#include "AnimatedTexture.hpp"

namespace fae {

class DynamicGameObject: public GameObject {
 public:
  void SetTexture(std::shared_ptr<AnimatedTexture> texture);

  void UseShaderProgram();

  void SetCoords(point3_t lb);

  virtual ~DynamicGameObject() { }

 protected:
  std::shared_ptr<AnimatedTexture> texture_;

  DynamicGameObject() {
    std::cout << "[->]\tDynamicGameObject" << std::endl;
  }
};

}  // namespace fae
