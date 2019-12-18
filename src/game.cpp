#include "Engine.hpp"

using namespace fae;

void game() {
    Renderer_p renderer = CreateRenderer(720, 1024, "4a-engine");

    //Shaders
    GlShader shader;
    std::string absoluteShadersPath = GetWorkingDirectory() + "shaders\\";
    GLuint shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    
    //Load textures and animations
    std::string absoluteResourcePath = GetWorkingDirectory() + "res\\";
    Texture_p room_tex = CreateTexture(absoluteResourcePath + "room1_small.png");
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
    fire_tex->SetFps(5);

    //Background
    StaticGameObject_p room = CreateStaticGameObject();
    room->SetTexture(room_tex);
    room->SetLayer(LAYER_BG);
    room->Scale({5, 5});
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
    hero->Scale({3, 3});
    hero->Move({100., 100.});

    //Fire animation
    AnimatedGameObject_p fire = CreateAnimatedGameObject();
    fire->SetTexture(fire_tex);
    fire->SetLayer(LAYER_BG);
    fire->Move({-35, 0});
    fire->Scale({5, 5});
    fire->SetShaderProgram(shaderProgram);

    //Set up scene
    GameScene_p scene = CreateGameScene();
    Camera_p orthCam = CreateCamera(720, 1024);
    scene->SetCamera(orthCam);
    scene->AddObject(hero);
    scene->AddObject(room);
    scene->AddObject(fire);

    //Handle keyboard events
    KeyboardControl_p ctrl = renderer->CreateKeyboardControl();
    ctrl->AddEventListener(hero);
    //OnFrame events
    renderer->AddEventListener(hero);
    renderer->AddEventListener(fire);
    renderer->AddEventListener(orthCam);  // For smooth camera
    //Whenever a player moves, camera needs to know,
    //where to slide
    hero->AddEventListener(orthCam);

    renderer->SetScene(scene);
    renderer->Start();
}