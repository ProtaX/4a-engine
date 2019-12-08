#pragma once
#include <list>
#include <functional>

#include "Core.hpp"
#include "GameObject.hpp"

namespace fae {

//Keyboard event dispatcher
class KeyboardControl {
private:
    GLFWwindow* window;

    std::list<std::function<void(Event&)>> m_callbacks;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (action == GLFW_RELEASE) return;
        KeyPressedEvent event(key);
        AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
        KeyboardControl* this_obj = reinterpret_cast<KeyboardControl*>(app->p_kb_ctl);
        for (std::function<void(Event&)> cb: this_obj->m_callbacks)
            cb(event);
    }

public:
    KeyboardControl(GLFWwindow* window);

    void AddEventListener(IControlable* object);

    void AddEventListener(std::shared_ptr<IControlable> object);
};

}