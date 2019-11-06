#pragma once

#include "glfw/glfw3.h"

namespace fae {

class Settings {
private:
    float windowH, windowW;
    int glwf_context_version_major, glwf_context_version_minor;
    int glfw_opengl_profile;
    int glfw_resizable;
    GLFWwindow* window;
    GLboolean glew_experimantal;
    GLenum glBlend_sfactor, glBlend_dfactor;

public:
    inline float WindowH() const { return windowH; }
    inline float WindowW() const { return windowW; }
    inline int GlwfContextVersionMajor() const { return glwf_context_version_major; }
    inline int GlwfContextVersionMinor() const { return glwf_context_version_minor; }
    inline int GlfwOpenglProfile() const { return glfw_opengl_profile; }
    inline int GlfwResizable() const { return glfw_resizable; }
    inline GLFWwindow* Window() const { return window; }
    inline GLboolean GlewExperimantal() const { return glew_experimantal; }
    inline GLenum GlBlendSfactor() const { return glBlend_sfactor; }
    inline GLenum GlBlendDfactor() const { return glBlend_dfactor; }
};

}