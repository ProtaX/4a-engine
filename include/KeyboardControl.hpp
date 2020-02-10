#pragma once
#include <list>
#include <functional>

#include "Core.hpp"
#include "GameObject.hpp"
#include "IListenable.hpp"

namespace fae {

//Keyboard event dispatcher
class KeyboardControl: public IListenable {
private:
    GLFWwindow* window;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (action == GLFW_RELEASE) return;
        KeyPressedEvent event(key);
        AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
        KeyboardControl* this_obj = reinterpret_cast<KeyboardControl*>(app->p_kb_ctl);
        std::cout << "key_callback count:" << this_obj->m_callbacks.size();
        for (std::function<void(Event&)> cb: this_obj->m_callbacks)
            cb(event);
    }

public:
    KeyboardControl(GLFWwindow* window);

    void AddEventListener(std::shared_ptr<IEventListener> object);
};

typedef std::shared_ptr<KeyboardControl> KeyboardControl_p;

}