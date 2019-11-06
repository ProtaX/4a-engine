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
        this->window_w = (float)windowW;
        this->window_h = (float)windowH;
        glwf_context_version_major = 3;
        glwf_context_version_minor = 3;
        glfw_opengl_profile = GLFW_OPENGL_CORE_PROFILE;
        glfw_resizable = GL_TRUE;
        window = NULL;
        glew_experimantal = GL_TRUE;
        glBlend_sfactor = GL_SRC_ALPHA;
        glBlend_dfactor = GL_ONE_MINUS_SRC_ALPHA;
        window_name = name;
        fps = 60;
        frame_time = 1./(double)fps;
    }

    GLFWwindow* Renderer::InitWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glwf_context_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glwf_context_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, glfw_opengl_profile);
        glfwWindowHint(GLFW_RESIZABLE, glfw_resizable);

        window = GLFWCall(glfwCreateWindow(window_w, window_h, window_name.c_str(), nullptr, nullptr));
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
        glfwSwapInterval(1);

        return window;
    }

    void Renderer::Start() {
        double start, wait_time, post_frame;
        while(!glfwWindowShouldClose(window)) {
            start = glfwGetTime();
            OnFrame();
            post_frame = glfwGetTime();
            wait_time = frame_time - (post_frame - start);
            if (wait_time <= 0)
                continue;
            Sleep(wait_time * 1000);
        }
    }

    void Renderer::OnFrame() {
        
    }

    Renderer::~Renderer() {
        glfwTerminate();
    }
} 
