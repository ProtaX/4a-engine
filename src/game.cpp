#include "Engine.hpp"

using namespace fae;

void game() {
  Renderer_p renderer = CreateRenderer(720, 1024, "4a-engine");

  // Shaders
  GlShader shader;
  std::string abs_shr_path = GetWorkingDirectory() + "\\shaders\\";
  GLuint shr_prog = shader.LinkFromFiles(abs_shr_path + "vs.glsl", abs_shr_path + "fs.glsl");

  // Load textures and animations
  std::string abs_res_path = GetWorkingDirectory() + "\\res\\";
  Texture_p room_tex = CreateTexture(abs_res_path + "room1_small.png");
  Texture_p head_tex = CreateTexture(abs_res_path + "ico.png");
  AnimatedTexture_p npc_tex = CreateAnimatedTexture(abs_res_path + "npc.png");
  AnimatedTexture_p step_left = CreateAnimatedTexture(abs_res_path + "step_left_batched.png");
  AnimatedTexture_p step_right = CreateAnimatedTexture(abs_res_path + "step_right_batched.png");
  AnimatedTexture_p step_down = CreateAnimatedTexture(abs_res_path + "step_down_batched.png");
  AnimatedTexture_p step_up = CreateAnimatedTexture(abs_res_path + "step_up_batched.png");
  AnimatedTexture_p idle = CreateAnimatedTexture(abs_res_path + "idle_static.png");
  AnimatedTexture_p fire_tex = CreateAnimatedTexture(abs_res_path + "bonfire.png");
  // Set up animations
  step_left->SetGrid(6, 1);
  step_right->SetGrid(6, 1);
  step_down->SetGrid(9, 1);
  step_up->SetGrid(9, 1);
  idle->SetFps(60);
  fire_tex->SetGrid(11, 1);
  fire_tex->SetFps(6);
  npc_tex->SetGrid(11, 1);
  npc_tex->SetFps(6);

  renderer->SetIcon(head_tex);

  // Background
  StaticGameObject_p room = CreateStaticGameObject();
  room->SetTexture(room_tex);
  room->SetLayer(0.f);
  room->Scale(5);
  room->SetShaderProgram(shr_prog);

  // Hero
  ControllableGameObject_p hero = CreateControllableGameObject();
  hero->SetIdleAnimation(idle);
  hero->SetLeftAnimation(step_left);
  hero->SetRightAnimation(step_right);
  hero->SetUpAnimation(step_up);
  hero->SetDownAnimation(step_down);
  hero->SetLayer(0.1f);
  hero->SetShaderProgram(shr_prog);
  hero->Scale(4);
  hero->Move({100., 10.});

  // Fire animation
  AnimatedGameObject_p fire = CreateAnimatedGameObject();
  fire->SetTexture(fire_tex);
  fire->SetLayer(0.2f);
  fire->Move({-35, 0});
  fire->Scale(5);
  fire->SetShaderProgram(shr_prog);

  // NPC
  AnimatedGameObject_p npc = CreateAnimatedGameObject();
  npc->SetTexture(npc_tex);
  npc->SetLayer(0.3f);
  npc->Scale(5);
  npc->SetShaderProgram(shr_prog);

  // Set up scene
  GameScene_p scene = CreateGameScene();
  Camera_p orthCam = CreateCamera(720, 1024);
  scene->SetCamera(orthCam);
  scene->AddObject(hero);
  scene->AddObject(room);
  scene->AddObject(fire);
  scene->AddObject(npc);

  // OnFrame events
  renderer->AddEventListener(EventType::Frame, hero);
  renderer->AddEventListener(EventType::Frame, fire);
  renderer->AddEventListener(EventType::Frame, npc);
  renderer->AddEventListener(EventType::Frame, orthCam);  // For smooth camera
  renderer->AddEventListener(EventType::KeyPressed, hero);
  // Whenever a player moves, camera needs to know,
  // where to slide
  hero->AddEventListener(EventType::PlayerMove, orthCam);

  renderer->SetScene(scene);
  renderer->Start();
}
