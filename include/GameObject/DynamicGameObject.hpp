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

public:
    DynamicGameObject() {
        std::cout << "[->]\tDynamicGameObject" << std::endl;
        segment_to_draw = 0;
        frames_until_next_segment = 1;
    }

    ~DynamicGameObject() { }

    void SetTexture(std::shared_ptr<AnimatedTexture> texture);

    virtual bool OnFrame(FrameEvent& e);

    void UseShaderProgram();

    void SetCoords(point3_t lb);

    void SetLength(int frames);

    virtual void OnEvent(Event& e);

    virtual bool OnKeyPressed(KeyPressedEvent& e);
};

typedef std::shared_ptr<DynamicGameObject> DynamicGameObject_p;

template<typename... _Args>
DynamicGameObject_p CreateDynamicGameObject(_Args&&... __args) {
    return std::make_shared<DynamicGameObject>(std::forward<_Args>(__args)...);
}

}