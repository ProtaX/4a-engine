#include "KeyboardControl.hpp"

namespace fae {

KeyboardControl::KeyboardControl(GLFWwindow* window,
                    int left_btn, 
                    int right_btn, 
                    int up_btn, 
                    int down_btn, 
                    int action_btn, 
                    int esc_btn) { 
        m_key_data.left_btn = left_btn;
        m_key_data.right_btn = right_btn;
        m_key_data.up_btn = up_btn;
        m_key_data.down_btn = down_btn;
        m_key_data.action_btn = action_btn;
        m_key_data.esc_btn = esc_btn;
        this->window = window;
        AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
        app->p_kb_ctl = (void*)this;
        glfwSetKeyCallback(window, reinterpret_cast<GLFWkeyfun>(&this->key_callback));
}

void KeyboardControl::AddEventListener(GameObject* object) {
    if (!object) {
       std::cout << "KeyboardControl::AddEventListener::Error: got null object" << std::endl;
       return;
    }
    std::function<void(Event&)> f = std::bind(&GameObject::OnEvent, object, std::placeholders::_1);
    m_callbacks.push_back(f);
}

}