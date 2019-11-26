#pragma once

#include <Core.hpp>
#include <GameObject.hpp>
#include <list>
#include <Camera.hpp>

namespace fae {

class GameScene {
private:
    //list sorted by z value of each GameObject
    std::list<GameObject> m_scene_storage;
    std::shared_ptr<Camera> p_camera;
public:
    GameScene() { }

    void AddObject(GameObject& obj);

    void SetCamera(std::shared_ptr<Camera> camera) { p_camera = camera; }

    //Draw every object on the scene
    void Draw();
};

}