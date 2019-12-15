#pragma once

#include "GameObject.hpp"
#include "Texture.hpp"
#include <functional>

namespace fae {

class StaticGameObject: public GameObject {
protected:
    std::shared_ptr<Texture> p_texture;
    
public:
    StaticGameObject() {
        std::cout << "[->]\tStaticGameObject" << std::endl;
    }

    virtual ~StaticGameObject() { }

    virtual void OnEvent(Event& e);

    virtual bool OnKeyPressed(KeyPressedEvent& e);
   
    virtual void ChangeState() { }

    void SetTexture(std::shared_ptr<Texture> texture);

    void SetCoords(point3_t lb);

    void UseShaderProgram();

};

typedef std::shared_ptr<StaticGameObject> StaticGameObject_p;

template<typename... _Args>
StaticGameObject_p CreateStaticGameObject(_Args&&... __args) {
    return std::make_shared<StaticGameObject>(std::forward<_Args>(__args)...);
}

}