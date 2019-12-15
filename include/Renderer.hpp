#pragma once

#include "Core.hpp"
#include <GameObject.hpp>
#include <Camera.hpp>
#include <GameScene.hpp>
#include "IListenable.hpp"
#include <list>

namespace fae {

class Renderer: public IListenable {
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
    std::shared_ptr<GameScene> p_scene;

    //Что делать каждый кадр
    void OnFrame(int frames_drawn);

public:
    Renderer(int window_h, int window_w, std::string name);

    GLFWwindow* InitWindow();

    void Start();

    void Stop();

    void SetScene(std::shared_ptr<GameScene> scene) { this->p_scene = scene; }

    void SetFps(unsigned int fps) { this->fps = fps; }

    void AddEventListener(std::shared_ptr<IEventListener> object);

    ~Renderer();
    
};

}