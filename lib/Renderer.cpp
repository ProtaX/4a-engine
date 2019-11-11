#include "Renderer.hpp"

namespace fae
{

Renderer::Renderer(int windowH, int windowW, std::string name, int shader) { 
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
    p_camera = std::make_unique<Camera>(windowH, windowW);
    default_shader_program = shader;
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
    glClear(GL_COLOR_BUFFER_BIT);
    //TODO: сделать влзможность задавать шейдер прямо в GameObject
    glUseProgram(default_shader_program);
    //Матрица проекции задается 1 раз
    glm::mat4 proj = p_camera->GetProj();
    GLint proj_location = glGetUniformLocation(default_shader_program, "proj");
    GLCall(glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj)));
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
    //Новая матрица вида передается в шейдер кажый раз, 
    //как надо сдивнуть камеру

    //TODO: сделать хранилище GameObject`ов, а использоваться оно
    //будет в этой функции. Также, здесь должна обновляться матрица вида
}

Renderer::~Renderer() {
    glfwTerminate();
}

void Renderer::DrawGameObject(GameObject& game_object) {
    //Пока оставим матрицу модели константной
    //При имплементации системы управления/NPC, ее надо будет менять
    //Также, пока используется только стандартный щейдер default_shader_program, 
    //а не собственный из экземпляра
    GLint model_location = glGetUniformLocation(default_shader_program, "model");
    GLCall(glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(game_object.GetModelMtx())));
    game_object.BindVertexArray();
    game_object.BindVertexBuffer();
    game_object.BindIndexBuffer();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  /* 6 - не должно быть магическим числом */
    game_object.UnbindVertexArray();
}

} 
