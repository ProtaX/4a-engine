#pragma once

#include <Core.hpp>
#include "GameObject.hpp"
#include "DynamicGameObject.hpp"
#include <vector>
#include <map>
#include <Camera.hpp>

namespace fae {

class GameScene {
private:
    //vector sorted by z value of each GameObject
    std::multimap<float, std::shared_ptr<GameObject>> m_scene_storage;
    std::shared_ptr<Camera> p_camera;
public:
    GameScene();

    ~GameScene() {
        std::cout << "[~] GameScene " << std::endl;
    }

    void AddObject(std::shared_ptr<GameObject> obj);

    void SetCamera(std::shared_ptr<Camera> camera) { p_camera = camera; }

    //Draw every object on the scene
    void Draw();

};

}