#pragma once

#include "GameObject.hpp"
#include "AnimatedTexture.hpp"
#include <functional>

namespace fae {

class DynamicGameObject: public GameObject {
protected:
    int segment_to_draw;
    int frames_until_next_segment;
    std::shared_ptr<AnimatedTexture> p_texture;

    DynamicGameObject() {
        std::cout << "[->]\tDynamicGameObject" << std::endl;
        segment_to_draw = 0;
        frames_until_next_segment = 1;
    }
public:

    virtual ~DynamicGameObject() { }

    void SetTexture(std::shared_ptr<AnimatedTexture> texture);

    void UseShaderProgram();

    void SetCoords(point3_t lb);

    void SetLength(int frames);

    virtual bool OnFrame(FrameEvent& e) = 0;

    virtual void OnEvent(Event& e) = 0;

};

}