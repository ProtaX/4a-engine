#pragma once

#include "Core.hpp"
#include "IControlable.hpp"

namespace fae {

class Camera: public IKeyControlable {
private:
    int h, w;
    int hBorder, wBorder;
    
    glm::mat4 proj;
    glm::mat4 view;

public:
    Camera(float windowH, float windowW);
    ~Camera() {
        std::cout << "[~] Camera " << std::endl;
     }

    void MoveCamera(point3_t p);

    void MoveCamera(glm::vec3& transVec);

    void OnEvent(Event& e);

    bool OnKeyPressed(KeyPressedEvent& e);

    glm::mat4 GetProj() const {
        return proj;
    }

    glm::mat4 GetVeiw() const {
        return view;
    }

    glm::mat4 GetProjView() const {
        return proj * view;
    }
};

typedef std::shared_ptr<Camera> Camera_p;

template<typename... _Args>
Camera_p CreateCamera(_Args&&... __args) {
    return std::make_shared<Camera>(std::forward<_Args>(__args)...);
}

}