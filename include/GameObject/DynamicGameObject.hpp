#pragma once

#include "GameObject.hpp"
#include "AnimatedTexture.hpp"
#include <functional>

namespace fae {

class DynamicGameObject: public GameObject {
protected:
    std::shared_ptr<AnimatedTexture> p_texture;

    DynamicGameObject() {
        std::cout << "[->]\tDynamicGameObject" << std::endl;
    }
public:

    virtual ~DynamicGameObject() { }

    void SetTexture(std::shared_ptr<AnimatedTexture> texture);

    void UseShaderProgram();

    void SetCoords(point3_t lb);

    virtual bool OnFrame(FrameEvent& e) = 0;

    virtual void OnEvent(Event& e) = 0;

};

}