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
    Renderer renderer(720, 1024, "4a-engine");

    //Shaders
    GlShader shader;
    std::string absoluteShadersPath = GetWorkingDirectory() + "shaders\\";
    GLuint shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    
    //Textures
    std::string absoluteResourcePath = GetWorkingDirectory() + "res\\";
    Texture_p room_tex = CreateTexture(absoluteResourcePath + "room1.png");
    AnimatedTexture_p anim_tex = CreateAnimatedTexture(absoluteResourcePath + "step_left_batched.png");
    anim_tex->SetGrid(7, 1);
    AnimatedTexture_p star_tex = CreateAnimatedTexture(absoluteResourcePath + "star.png");
    star_tex->SetGrid(5, 1);

    //Background
    StaticGameObject_p room = CreateStaticGameObject();
    room->SetTexture(room_tex);
    room->SetLayer(LAYER_BG);
    room->SetShaderProgram(shaderProgram);

    //Hero
    ControllableGameObject_p hero = CreateControllableGameObject();
    hero->SetTexture(anim_tex);
    hero->SetLayer(LAYER_HERO);
    hero->SetShaderProgram(shaderProgram);
    hero->Scale({2.9f, 2.5f});
    hero->Move({100., 100.});

    //Animation
    AnimatedGameObject_p star = CreateAnimatedGameObject();
    star->SetTexture(star_tex);
    star->SetLayer(LAYER_HERO);
    star->SetShaderProgram(shaderProgram);

    //Set up scene
    GameScene_p scene = CreateGameScene();
    Camera_p orthCam = CreateCamera(720, 1024);
    scene->SetCamera(orthCam);
    scene->AddObject(hero);
    scene->AddObject(room);
    scene->AddObject(star);

    //Handle keyboard events
    KeyboardControl_p ctrl = renderer.CreateKeyboardControl();
    ctrl->AddEventListener(hero);
    ctrl->AddEventListener(orthCam);
    //OnFrame events
    renderer.AddEventListener(hero);
    renderer.AddEventListener(star);

    renderer.SetScene(scene);
    renderer.Start();
    //TODO: сделать вызов glfwTerminate();
}