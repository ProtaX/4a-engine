#include "Camera.hpp"
#include <functional>

namespace fae {

Camera::Camera(float windowH, float windowW) {
        view = glm::lookAt(
            glm::vec3(-windowW/2, -windowH/2, 1.0f),
            glm::vec3(-windowW/2, -windowH/2, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        proj = glm::ortho(0.0f, windowW, 0.0f, windowH, 0.0f, 1.0f);
}

void Camera::MoveCamera(point3_t p) {
        view = glm::translate(view, glm::vec3(p.x, p.y, p.z));
}

void Camera::MoveCamera(glm::vec3& transVec) {
    view = glm::translate(view, transVec);
}

void Camera::OnEvent(Event& e) {
    EventDispatcher disp(e);
    
    disp.Dispatch<KeyPressedEvent>(std::bind(&OnKeyPressed, this, std::placeholders::_1));
}

bool Camera::OnKeyPressed(KeyPressedEvent& e) {
    int keycode = e.GetKeyCode();
    
    if (keycode == GLFW_KEY_W) {
        MoveCamera({0., -5.});
    }
    else if (keycode == GLFW_KEY_A) {
        MoveCamera({5.});
    }
    else if (keycode == GLFW_KEY_S) {
        MoveCamera({0., 5.});
    }
    else if (keycode == GLFW_KEY_D) {
        MoveCamera({-5.});
    }
    else return false;
    return true;
}

}