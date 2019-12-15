#include "Renderer.hpp"

namespace fae
{

Renderer::Renderer(int windowH, int windowW, std::string name, bool init_window) { 
    window_w = (float)windowW;
    window_h = (float)windowH;
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

    if (init_window)
        InitWindow();
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
    AppInfo* p_app_info = new AppInfo();
    glfwSetWindowUserPointer(window, (void*)p_app_info);
    
    return window;
}

void Renderer::Start() {
    double start, wait_time, post_frame;

    int frame_counter = 0;
    double render_start = glfwGetTime();
    frame_time = 1./(double)fps;
    while(!glfwWindowShouldClose(window)) {
        start = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT);
        OnFrame(frame_counter);
        glfwSwapBuffers(window);
        post_frame = glfwGetTime();
        wait_time = frame_time - (post_frame - start);
        if (wait_time <= 0)
            continue;
        Sleep(wait_time * 1000);

        frame_counter++;
        if ((post_frame - render_start) >= 1) {
            std::cout << "[FPS] " << frame_counter << std::endl;
            frame_counter = 0;
            render_start++;
        }
    }
}

void Renderer::OnFrame(int frames_drawn) {
    FrameEvent e(frames_drawn);
    for (auto& cb: m_callbacks)
        cb(e);
    glfwPollEvents();
    p_scene->Draw();
}

Renderer::~Renderer() {
    std::cout << "[~] Renderer " << std::endl;
    AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
    delete app;
    //glfwTerminate();
}

void Renderer::AddEventListener(std::shared_ptr<IEventListener> object) {
    if (!object) {
       std::cout << "Renderer::AddEventListener::Error: got null object" << std::endl;
       return;
    }
    std::function<void(Event&)> f = std::bind(&IEventListener::OnEvent, object.get(), std::placeholders::_1);
    m_callbacks.push_back(f);
}

} 
