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
        m_move_to = {};
}

void Camera::MoveCamera(point3_t p) {
        view = glm::translate(view, glm::vec3(p.x, p.y, p.z));
}

void Camera::MoveCamera(glm::vec3& transVec) {
    view = glm::translate(view, transVec);
}

void Camera::OnEvent(Event& e) {
    EventDispatcher disp(e);
    
    disp.Dispatch<FrameEvent>(std::bind(&OnFrame, this, std::placeholders::_1));
    disp.Dispatch<PlayerMoveEvent>(std::bind(&OnPlayerMove, this, std::placeholders::_1));
}

bool Camera::OnPlayerMove(PlayerMoveEvent& e) {
    m_frames_left = e.GetFrames();
    if (!m_frames_left)
        return false;
    m_move_to = e.GetMove();
    m_move_to.x *= -1. / ((float)m_frames_left);
    m_move_to.y *= -1. / ((float)m_frames_left);
    m_move_to.z *= -1. / ((float)m_frames_left);

    return true;
}

bool Camera::OnFrame(FrameEvent& e) {
    if (m_frames_left) {
        MoveCamera(m_move_to);
        m_frames_left--;
    }
    return true;
}

}