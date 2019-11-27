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

    //TODO: эта функиця, при вызове ее из glfw, не получает указатель this, 
    //а, следовательно, не может получить доступ к m_callbacks
    //возможно, стоит обернуть ее в glfwSetKeyCallback в std::bind
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        std::cout << "Key Pressed\n";
        KeyPressedEvent event(key);
        /*
        for (std::function<void(Event&)> cb: m_callbacks) {
            std::cout << "calling\n";
            cb(event);
        }
        */
    }

public:
    KeyboardControl(GLFWwindow* window,
                    int left_btn = GLFW_KEY_A, 
                    int right_btn = GLFW_KEY_D, 
                    int up_btn = GLFW_KEY_W, 
                    int down_btn = GLFW_KEY_S, 
                    int action_btn = GLFW_KEY_ENTER, 
                    int esc_btn = GLFW_KEY_ESCAPE) { 
        m_key_data.left_btn = left_btn;
        m_key_data.right_btn = right_btn;
        m_key_data.up_btn = up_btn;
        m_key_data.down_btn = down_btn;
        m_key_data.action_btn = action_btn;
        m_key_data.esc_btn = esc_btn;
        this->window = window;
        glfwSetKeyCallback(window, reinterpret_cast<GLFWkeyfun>(&this->key_callback));
    }

    void PushCallback(GameObject* object) {
        std::function<void(Event&)> f = std::bind(&GameObject::OnEvent, object, std::placeholders::_1);
        m_callbacks.push_back(f);
    }

};

}