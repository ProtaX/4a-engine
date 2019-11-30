#pragma once

#include <Core.hpp>
#include <GameObject.hpp>
#include <vector>
#include <Camera.hpp>

namespace fae {

class GameScene {
private:
    //vector sorted by z value of each GameObject
    std::vector<GameObject> m_scene_storage;
    std::shared_ptr<Camera> p_camera;
public:
    GameScene();

    ~GameScene() {
        std::cout << "[~] GameScene " << std::endl;
    }

    GameObject* GetObjectById(game_object_id id);

    //When object is added to the scene, it can be
    // accessed ONLY with id returned by AddObject
    game_object_id AddObject(GameObject& obj);

    void SetCamera(std::shared_ptr<Camera> camera) { p_camera = camera; }

    //Draw every object on the scene
    void Draw();

};

}