#pragma once

#include "DynamicGameObject.hpp"
#include "IControlable.hpp"

namespace fae {

class ControllableGameObject: public DynamicGameObject, public IKeyControlable {
public:
    ControllableGameObject() {
        std::cout << "[->]\tControllableGameObject" << std::endl;
    }

    virtual ~ControllableGameObject() { }

    void OnEvent(Event& e) final;

    bool OnFrame(FrameEvent& e);

    bool OnKeyPressed(KeyPressedEvent& e) final;
};

typedef std::shared_ptr<ControllableGameObject> ControllableGameObject_p;

template<typename... _Args>
ControllableGameObject_p CreateControllableGameObject(_Args&&... __args) {
    return std::make_shared<ControllableGameObject>(std::forward<_Args>(__args)...);
}

}