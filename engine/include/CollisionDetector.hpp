#pragma once

#include "Core.hpp"
#include "GameObject.hpp"
#include "GameScene.hpp"

#include <tuple>

namespace fae {

class CollisionDetector {
private:
  //Сколько пикселей вокруг для взаимодействия
  int m_near_px;

  bool TestCollide(std::shared_ptr<GameObject> left, std::shared_ptr<GameObject> right) {
    std::cout << "Testing collision\n";
  }
public:
  CollisionDetector(int near_px = 20): m_near_px(near_px) { }

  void Detect(GameScene_p scene) {

  }
};

// Экземпляры этого класса - олицетворение столкновений объектов движка,
// которые должны произойти. На события каждого такого экземпляра можно подписаться
class Collision: public ICollidable {
private:
  std::shared_ptr<GameObject> m_left;
  std::shared_ptr<GameObject> m_right;

public:
  inline void SetLeft(std::shared_ptr<GameObject> left) { m_left = left; }
  inline void SetRight(std::shared_ptr<GameObject> right) { m_right = right; }

  // Проверяет объекты на столкновение и дергает все cb
  void Check() {
    //rt, rb, lb, lt
    std::tuple<point3_t, point3_t, point3_t, point3_t> v_left = m_left->GetModelVerticies();
    std::tuple<point3_t, point3_t, point3_t, point3_t> v_right = m_right->GetModelVerticies();

    /*
    // Хотя бы 1 вершина из v_left входит внутрь v_right
    for (int i = 0; i < 4; ++i) {
      point3_t left_vertex = std::get<i>(v_left);
      //TODO: разобраться с итерацией
      if () {

      }
    }
    */
  }
};

}  // namespace fae