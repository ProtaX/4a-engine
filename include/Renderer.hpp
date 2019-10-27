#pragma once

#include "glew/glew.h"
#include "glew/glfw3.h"
#include <iostream>

//Фуцнкия, обернутая в этот макро, не может вернуть занчение
#define GLCall(x) \
        GLClearErrors(); \
        x; \
        GLGetErrors(__LINE__) \

#define GLFWCall(x) \
        x; \
        do { \
            const char* errMsg; \
            const char** errMsgLoc = &errMsg; \
            int code = glfwGetError(errMsgLoc); \
            if (code != GLFW_NO_ERROR) { \
                std::cout << "GLFW error: " << errMsg << std::endl; \
                glfwTerminate(); \
            } \
        } while (0) \

void GLClearErrors();

void GLGetErrors(int line) ;

namespace fae {

class Renderer {
private:
    float windowH, windowW;
    int glwf_context_version_major, glwf_context_version_minor;
    int glfw_opengl_profile;
    int glfw_resizable;
    GLFWwindow* window;
    GLboolean glew_experimantal;
    GLenum glBlend_sfactor, glBlend_dfactor;
    std::string windowName;
    unsigned int fps;
    int stopRenderer = 0;

    //Что делать каждый кадр
    void OnFrame();

public:
    Renderer(int windowH, int windowW, std::string name);

    GLFWwindow* InitWindow();

    void Start();

    void Stop();

    ~Renderer();
    
};

}