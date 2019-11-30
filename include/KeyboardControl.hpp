#pragma once
#include "Core.hpp"
#include "GameObject.hpp"
#include "Event.hpp"
#include <list>
#include <functional>

namespace fae {

//Keyboard event dispatcher
class KeyboardControl {
private:
    struct {
        int left_btn,
        right_btn,
        up_btn,
        down_btn,
        action_btn,
        esc_btn;
    } m_key_data;
    GLFWwindow* window;

    std::list<std::function<void(Event&)>> m_callbacks;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (action == GLFW_RELEASE) return;
        std::cout << "Key Pressed\n";
        KeyPressedEvent event(key);
        AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
        KeyboardControl* this_obj = reinterpret_cast<KeyboardControl*>(app->p_kb_ctl);
        for (std::function<void(Event&)> cb: this_obj->m_callbacks)
            cb(event);
    }

public:
    KeyboardControl(GLFWwindow* window,
                    int left_btn = GLFW_KEY_A, 
                    int right_btn = GLFW_KEY_D, 
                    int up_btn = GLFW_KEY_W, 
                    int down_btn = GLFW_KEY_S, 
                    int action_btn = GLFW_KEY_ENTER, 
                    int esc_btn = GLFW_KEY_ESCAPE);

    void PushCallback(GameObject* object);

};

}