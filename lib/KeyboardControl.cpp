#include "KeyboardControl.hpp"

namespace fae {

KeyboardControl::KeyboardControl(GLFWwindow* window) { 
        this->window = window;
        AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
        app->p_kb_ctl = (void*)this;
        glfwSetKeyCallback(window, reinterpret_cast<GLFWkeyfun>(&this->key_callback));
}

void KeyboardControl::AddEventListener(IControlable* object) {
    if (!object) {
       std::cout << "KeyboardControl::AddEventListener::Error: got null object" << std::endl;
       return;
    }
    std::function<void(Event&)> f = std::bind(&IControlable::OnEvent, object, std::placeholders::_1);
    m_callbacks.push_back(f);
}

void KeyboardControl::AddEventListener(std::shared_ptr<IControlable> object) {
    if (!object) {
       std::cout << "KeyboardControl::AddEventListener::Error: got null object" << std::endl;
       return;
    }
    std::function<void(Event&)> f = std::bind(&IControlable::OnEvent, object.get(), std::placeholders::_1);
    m_callbacks.push_back(f);
}

}