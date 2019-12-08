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
#include "DynamicGameObject.hpp"
#include "StaticGameObject.hpp"

using namespace fae;

//Increments when a new Texture object is created 
GLuint Texture::vaccant_tex_target = GL_TEXTURE0;

int main() {
    float windowH = 720.0f, windowW = 1024.0f;  // px

    Renderer renderer(windowH, windowW, "4a-engine");
    GLFWwindow* window = renderer.InitWindow();

    //Shaders
    GlShader shader;
    std::string absoluteShadersPath = GetWorkingDirectory() + "shaders\\";
    GLuint shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    //Textures
    std::string absoluteResourcePath = GetWorkingDirectory() + "res\\";
    std::shared_ptr<Texture> room_tex = std::make_shared<Texture>(absoluteResourcePath + "room1.png");
    std::shared_ptr<Texture> hero_tex = std::make_shared<Texture>(absoluteResourcePath + "left1.png");
    std::shared_ptr<Texture> hero2_tex = std::make_shared<Texture>(absoluteResourcePath + "left2.png");

    //TEST
    std::shared_ptr<AnimatedTexture> anim_tex = std::make_shared<AnimatedTexture>(absoluteResourcePath + "batched_texture.png");
    anim_tex->SetGrid(5, 1);

    //Orth Camera
    //TODO: why shared?
    std::shared_ptr<Camera> orthCam = std::make_shared<Camera>(windowW, windowH);
    //Scene containing all game objects
    std::shared_ptr<GameScene> scene = std::make_shared<GameScene>();
    scene->SetCamera(orthCam);
    //Controls
    KeyboardControl* ctrl = new KeyboardControl(window);

    //Objects can be added in any order, they 
    //will be sorted by LAYER in the scene storage
    //Background
    std::shared_ptr<StaticGameObject> room = std::make_shared<StaticGameObject>();
    room->SetTexture(room_tex);
    room->SetLayer(LAYER_BG);
    room->SetShaderProgram(shaderProgram);
    
    //Hero
    std::shared_ptr<StaticGameObject> hero = std::make_shared<StaticGameObject>();
    hero->SetTexture(hero_tex);
    hero->SetLayer(LAYER_HERO);
    hero->SetShaderProgram(shaderProgram);
    hero->Scale({2.9f, 2.5f});
    hero->Move({100., 100.});

    //Hero 2
    std::shared_ptr<DynamicGameObject> anim = std::make_shared<DynamicGameObject>();
    anim->SetTexture(anim_tex);
    anim->SetLayer(LAYER_HERO);
    anim->SetShaderProgram(shaderProgram);

    //Objects in the scene are no longer cannot be accessed from here
    //To access uploaded object there is a game_object_id
    game_object_id hero_id = scene->UploadObject(hero);
    scene->UploadObject(room);
    scene->UploadObject(anim);
    //OnEvent() function of IControlable object will be called 
    //whenever a key event occurs
    ctrl->AddEventListener(scene->GetObjectById(hero_id));
    //ctrl->AddEventListener(scene->GetObjectById(anim_id));
    ctrl->AddEventListener(orthCam);

    renderer.SetScene(scene);
    renderer.Start();
    //TODO: сделать вызов glfwTerminate();
}