#include "Engine.hpp"

using namespace fae;

void game() {
    Renderer_p renderer = CreateRenderer(720, 1024, "4a-engine");
    
    //Shaders
    GlShader shader;
    std::string absoluteShadersPath = GetWorkingDirectory() + "\\shaders\\";
    GLuint shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    
    //Load textures and animations
    std::string absoluteResourcePath = GetWorkingDirectory() + "\\res\\";
    Texture_p room_tex = CreateTexture(absoluteResourcePath + "room1_small.png");
    Texture_p head_tex = CreateTexture(absoluteResourcePath + "ico.png");
    AnimatedTexture_p npc_tex = CreateAnimatedTexture(absoluteResourcePath + "npc.png");
    AnimatedTexture_p step_left = CreateAnimatedTexture(absoluteResourcePath + "step_left_batched.png");
    AnimatedTexture_p step_right = CreateAnimatedTexture(absoluteResourcePath + "step_right_batched.png");
    AnimatedTexture_p step_down = CreateAnimatedTexture(absoluteResourcePath + "step_down_batched.png");
    AnimatedTexture_p step_up = CreateAnimatedTexture(absoluteResourcePath + "step_up_batched.png");
    AnimatedTexture_p idle = CreateAnimatedTexture(absoluteResourcePath + "idle_static.png");
    AnimatedTexture_p fire_tex = CreateAnimatedTexture(absoluteResourcePath + "bonfire.png");
    //Set up animations
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

    //Background
    StaticGameObject_p room = CreateStaticGameObject();
    room->SetTexture(room_tex);
    room->SetLayer(LAYER_BG);
    room->Scale(5);
    room->SetShaderProgram(shaderProgram);

    //Hero
    ControllableGameObject_p hero = CreateControllableGameObject();
    hero->SetIdleAnimation(idle);
    hero->SetLeftAnimation(step_left);
    hero->SetRightAnimation(step_right);
    hero->SetUpAnimation(step_up);
    hero->SetDownAnimation(step_down);
    hero->SetLayer(LAYER_HERO);
    hero->SetShaderProgram(shaderProgram);
    hero->Scale(4);
    hero->Move({100., 10.});

    //Fire animation
    AnimatedGameObject_p fire = CreateAnimatedGameObject();
    fire->SetTexture(fire_tex);
    fire->SetLayer(LAYER_BG);
    fire->Move({-35, 0});
    fire->Scale(5);
    fire->SetShaderProgram(shaderProgram);

    //NPC
    AnimatedGameObject_p npc = CreateAnimatedGameObject();
    npc->SetTexture(npc_tex);
    npc->SetLayer(LAYER_HERO + 0.1f);
    npc->Scale(5);
    npc->SetShaderProgram(shaderProgram);

    //Set up scene
    GameScene_p scene = CreateGameScene();
    Camera_p orthCam = CreateCamera(720, 1024);
    scene->SetCamera(orthCam);
    scene->AddObject(hero);
    scene->AddObject(room);
    scene->AddObject(fire);
    scene->AddObject(npc);

    //OnFrame events
    renderer->AddFrameListener(hero);
    renderer->AddFrameListener(fire);
    renderer->AddFrameListener(npc);
    renderer->AddFrameListener(orthCam);  // For smooth camera
    renderer->AddKeyListener(hero);
    //Whenever a player moves, camera needs to know,
    //where to slide
    hero->AddMoveListener(orthCam);

    renderer->SetScene(scene);
    renderer->Start();
}