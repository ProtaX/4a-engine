#pragma once

#include "Core.hpp"

namespace fae {

class Camera {
private:
    int h, w;
    int hBorder, wBorder;
    
    glm::mat4 proj;
    glm::mat4 view;

    glm::vec3 translateVec;

public:
    Camera(float windowH, float windowW);
    ~Camera() {
        std::cout << "[~] Camera " << std::endl;
     }

    void MoveCamera(float offX, float offY, float offZ);

    void MoveCamera(glm::vec3& transVec);

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

}