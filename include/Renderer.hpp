#pragma once

#include "Core.hpp"
#include <GameObject.hpp>
#include <Camera.hpp>
#include <GameScene.hpp>
#include "IListenable.hpp"
#include "KeyboardControl.hpp"
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
    Renderer(int window_h, int window_w, std::string name, bool init_window = true);

    GLFWwindow* InitWindow();

    void Start();

    void Stop();

    void SetScene(std::shared_ptr<GameScene> scene) { this->p_scene = scene; }

    void SetFps(unsigned int fps) { this->fps = fps; }

    void AddEventListener(std::shared_ptr<IEventListener> object) final;

    KeyboardControl_p CreateKeyboardControl() {
        return std::make_shared<KeyboardControl>(window);
    }

    ~Renderer();
    
};

typedef std::unique_ptr<Renderer> Renderer_p;

template<typename... _Args>
Renderer_p CreateRenderer(_Args&&... __args) {
    return std::make_unique<Renderer>(std::forward<_Args>(__args)...);
}

}