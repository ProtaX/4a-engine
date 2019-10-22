#include "Renderer.hpp"

void GLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

void GLGetErrors(int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL error]: 0x" << std::hex << error << " on line " << std::dec << line << "\n";
    }
}

namespace fae
{
    Renderer::Renderer(int windowH, int windowW, std::string name) { 
        this->windowW = (float)windowW;
        this->windowH = (float)windowH;
        glwf_context_version_major = 3;
        glwf_context_version_minor = 3;
        glfw_opengl_profile = GLFW_OPENGL_CORE_PROFILE;
        glfw_resizable = GL_TRUE;
        window = NULL;
        glew_experimantal = GL_TRUE;
        glBlend_sfactor = GL_SRC_ALPHA;
        glBlend_dfactor = GL_ONE_MINUS_SRC_ALPHA;
        windowName = name;
        fps = 60;
    }

    GLFWwindow* Renderer::InitWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glwf_context_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glwf_context_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, glfw_opengl_profile);
        glfwWindowHint(GLFW_RESIZABLE, glfw_resizable);

        window = GLFWCall(glfwCreateWindow(windowW, windowH, windowName.c_str(), nullptr, nullptr));
        if (window == nullptr) 
	        return nullptr;
        
        glfwMakeContextCurrent(window);
        glewExperimental = glew_experimantal;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        int FBwidth, FBheight;
        glfwGetFramebufferSize(window, &FBwidth, &FBheight);
        glViewport(0, 0, FBwidth, FBheight);
        glBlendFunc(glBlend_sfactor, glBlend_dfactor);
        glEnable(GL_BLEND);

        return window;
    }

    void Renderer::Start() {
        while(!glfwWindowShouldClose(window)) {
            OnFrame();
        }
    }

    void Renderer::OnFrame() {
        
    }

    Renderer::~Renderer() {
        glfwTerminate();
    }
} 
