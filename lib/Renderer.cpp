#include "Renderer.hpp"

#include "Core.hpp"

namespace fae {

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (action == GLFW_RELEASE) return;
  KeyPressedEvent event(key);
  AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window));
  Renderer* r = reinterpret_cast<Renderer*>(app->renderer);
  r->HandleEvent(event);
}

Renderer::Renderer(int windowH, int windowW, std::string name, bool init_window) noexcept {
  window_w_ = static_cast<float>(windowW);
  window_h_ = static_cast<float>(windowH);
  glwf_context_v_mj_ = 3;
  glwf_context_v_mn_ = 3;
  glfw_opengl_profile_ = GLFW_OPENGL_CORE_PROFILE;
  glfw_resizable_ = GL_TRUE;
  window_ = NULL;
  glew_experimantal_ = GL_TRUE;
  glBlend_sfactor_ = GL_SRC_ALPHA;
  glBlend_dfactor_ = GL_ONE_MINUS_SRC_ALPHA;
  window_name_ = name;
  fps_ = 60U;
  frame_time_ = 1.f/static_cast<float>(fps_);
  fae_app_info.renderer = this;
  if (init_window)
    InitWindow();
}

void Renderer::InitWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glwf_context_v_mj_);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glwf_context_v_mn_);
  glfwWindowHint(GLFW_OPENGL_PROFILE, glfw_opengl_profile_);
  glfwWindowHint(GLFW_RESIZABLE, glfw_resizable_);

  window_ = GLFWCall(glfwCreateWindow(window_w_, window_h_, window_name_.c_str(), nullptr, nullptr));
  if (window_ == nullptr)
    return;

  glfwSetKeyCallback(window_, key_callback);
  glfwMakeContextCurrent(window_);
  glewExperimental = glew_experimantal_;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
    return;
  }

  int FBwidth, FBheight;
  glfwGetFramebufferSize(window_, &FBwidth, &FBheight);
  glViewport(0, 0, FBwidth, FBheight);
  glBlendFunc(glBlend_sfactor_, glBlend_dfactor_);
  glEnable(GL_BLEND);
  glfwSetWindowUserPointer(window_, reinterpret_cast<void*>(&fae_app_info));
}

void Renderer::Start() {
  double start, wait_time, post_frame;

  uint32_t frame_counter = 0U;
  double render_start = glfwGetTime();
  frame_time_ = 1.f/static_cast<float>(fps_);
  while (!glfwWindowShouldClose(window_)) {
    start = glfwGetTime();
    glClear(GL_COLOR_BUFFER_BIT);
    OnFrame(frame_counter);
    glfwSwapBuffers(window_);
    post_frame = glfwGetTime();
    wait_time = frame_time_ - (post_frame - start);
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
  FrameEvent e(frames_drawn, fps_);
  auto& cbs = GetCallbacks(EventType::Frame);
  for (auto& cb : cbs)
    cb(static_cast<const Event&>(e));
  glfwPollEvents();
  scene_->Draw();
}

Renderer::~Renderer() {
  std::cout << "[~] Renderer " << std::endl;
  AppInfo* app = reinterpret_cast<AppInfo*>(glfwGetWindowUserPointer(window_));
  delete app;
  // glfwTerminate();
}

void Renderer::AddEventListener(EventType t, std::shared_ptr<IEventListener> object) {
  if (!object) {
     std::cout << "Renderer::AddEventListener::Error: got null object" << std::endl;
     return;
  }
  EventCB f = std::bind(&IEventListener::OnEvent, object.get(), std::placeholders::_1);
  AddCallback(t, f);
}

bool Renderer::HandleEvent(const KeyPressedEvent& e) {
  auto& cbs = GetCallbacks(EventType::KeyPressed);
  for (auto& cb : cbs)
    cb(static_cast<const Event&>(e));
  return true;
}

void Renderer::SetIcon(Texture_p ico) const {
  GLFWimage icons[1];
  icons[0].pixels = ico->GetPixelData();
  icons[0].height = ico->GetH();
  icons[0].width = ico->GetW();
  glfwSetWindowIcon(window_, 1, icons);
}

}  // namespace fae
