#pragma once

#include "Core.hpp"

#include <GameObject.hpp>
#include <Camera.hpp>

namespace fae {

class Renderer {
private:
    float window_h, window_w;
    int glwf_context_version_major, glwf_context_version_minor;
    int glfw_opengl_profile;
    int glfw_resizable;
    GLFWwindow* window;
    GLboolean glew_experimantal;
    GLenum glBlend_sfactor, glBlend_dfactor;
    std::string window_name;
    unsigned int fps;
    double frame_time;
    int stopRenderer = 0;
    std::unique_ptr<Camera> p_camera;
    int default_shader_program;

    //Что делать каждый кадр
    void OnFrame();

    //TODO: временная функция
    void MoveMainCharacter();

    void DrawGameObject(GameObject& game_object);

public:
    Renderer(int window_h, int window_w, std::string name, int shader);

    GLFWwindow* InitWindow();

    void Start();

    void Stop();

    ~Renderer();

    inline void SetShader(int shader) { this->default_shader_program = shader; }
    
};

}