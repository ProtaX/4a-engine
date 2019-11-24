#pragma once

#include <Core.hpp>
#include <GameObject.hpp>
#include <list>

namespace fae {

class GameScene {
private:
    //list sorted by z value of each GameObject
    std::list<GameObject> scene_storage;
public:
    GameScene() { }

    void AddObject(GameObject& obj);
};

}