#include "Core.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "GlShader.hpp"
#include "KeyboardControl.hpp"
#include "Texture.hpp"
#include "AnimatedTexture.hpp"
#include "ControllableGameObject.hpp"
#include "AnimatedGameObject.hpp"
#include "StaticGameObject.hpp"
#include "GameScene.hpp"

using namespace fae;

//Increments when a new Texture object is created 
GLuint Texture::vaccant_tex_target = GL_TEXTURE0;

int main() {
    Renderer_p renderer = CreateRenderer(720, 1024, "4a-engine");

    //Shaders
    GlShader shader;
    std::string absoluteShadersPath = GetWorkingDirectory() + "shaders\\";
    GLuint shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    
    //Textures
    std::string absoluteResourcePath = GetWorkingDirectory() + "res\\";
    Texture_p room_tex = CreateTexture(absoluteResourcePath + "room1_small.png");
    AnimatedTexture_p step_left = CreateAnimatedTexture(absoluteResourcePath + "step_left_batched.png");
    AnimatedTexture_p step_right = CreateAnimatedTexture(absoluteResourcePath + "step_right_batched.png");
    AnimatedTexture_p idle = CreateAnimatedTexture(absoluteResourcePath + "idle_static.png");
    step_left->SetGrid(6, 1);
    step_right->SetGrid(6, 1);
    idle->SetFps(6);
    AnimatedTexture_p fire_tex = CreateAnimatedTexture(absoluteResourcePath + "bonfire.png");
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
    hero->SetUpAnimation(idle);
    hero->SetDownAnimation(idle);
    hero->SetLayer(LAYER_HERO);
    hero->SetShaderProgram(shaderProgram);
    hero->Scale({3, 3});
    hero->Move({100., 100.});

    //Animation
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
    //Smooth camera
    renderer->AddEventListener(orthCam);
    //Whenever a player moves, camera need to know,
    //where to slide
    hero->AddEventListener(orthCam);

    renderer->SetScene(scene);
    renderer->Start();
    //TODO: сделать вызов glfwTerminate();
}