#pragma once

#include "GameObject.hpp"
#include "AnimatedTexture.hpp"
#include <functional>

namespace fae {

class DynamicGameObject: public GameObject {
protected:
    int segment_to_draw;
    std::shared_ptr<AnimatedTexture> p_texture;

public:
    DynamicGameObject() {
        std::cout << "[->]\tDynamicGameObject" << std::endl;
        segment_to_draw = 0;
    }

    ~DynamicGameObject() { }

    void SetTexture(std::shared_ptr<AnimatedTexture> texture);

    virtual void ChangeState();

    void UseShaderProgram();

    void SetCoords(point3_t lb);

    virtual void OnEvent(Event& e);

    virtual bool OnKeyPressed(KeyPressedEvent& e);
};

}