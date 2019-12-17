#pragma once

#include "DynamicGameObject.hpp"

namespace fae {

class AnimatedGameObject: public DynamicGameObject {
private:
    int segment_to_draw;

public:
    AnimatedGameObject() {
        std::cout << "[->]\tAnimatedGameObject" << std::endl;
        segment_to_draw = 0;
    }

    virtual ~AnimatedGameObject() { }

    bool OnFrame(FrameEvent& e) final;

    void OnEvent(Event& e) final;
};

typedef std::shared_ptr<AnimatedGameObject> AnimatedGameObject_p;

template<typename... _Args>
AnimatedGameObject_p CreateAnimatedGameObject(_Args&&... __args) {
    return std::make_shared<AnimatedGameObject>(std::forward<_Args>(__args)...);
}

}