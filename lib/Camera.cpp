#include "Camera.hpp"

namespace fae {

Camera::Camera(float windowH, float windowW) {
        view = glm::lookAt(
            glm::vec3(-windowH/2, -windowW/2, 1.0f),
            glm::vec3(-windowH/2, -windowW/2, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        proj = glm::ortho(0.0f, windowH, 0.0f, windowW, 0.0f, 1.0f);
        translateVec = glm::vec3(0.0f);
}

void Camera::MoveCamera(float offX, float offY, float offZ) {
        translateVec[0] += offX;
        translateVec[1] += offY;
        translateVec[2] += offZ;
        view = glm::translate(view, translateVec);
}

void Camera::MoveCamera(glm::vec3& transVec) {
    translateVec = transVec;
    view = glm::translate(view, translateVec);
}

}