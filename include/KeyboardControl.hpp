#pragma once
#include "Core.hpp"
#include <list>

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
    }

};