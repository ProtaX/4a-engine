#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <map>

#include "Camera.hpp"
#include "GameObject/DynamicGameObject.hpp"
#include "GameObject/GameObject.hpp"

namespace fae {

class GameScene {
 public:
  GameScene() noexcept {}

  ~GameScene() {
    std::cout << "[~] GameScene " << std::endl;
  }

  void AddObject(std::shared_ptr<GameObject> obj);

  void SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

  void Draw() const;

 private:
  // Sorted by z value of each GameObject
  std::multimap<float, std::shared_ptr<GameObject>> scene_storage_;
  std::shared_ptr<Camera> camera_;
};

typedef std::shared_ptr<GameScene> GameScene_p;

template<typename... _Args>
GameScene_p CreateGameScene(_Args&&... __args) {
  return std::make_shared<GameScene>(std::forward<_Args>(__args)...);
}

}  // namespace fae
