#define TEST_BUILD

#include <string.h>

#include "Core.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "GlShader.hpp"
#include "KeyboardControl.hpp"
#include "Texture.hpp"

using namespace fae;

//Increments when a new Texture object is created 
GLuint Texture::vaccant_tex_target = GL_TEXTURE0;

int main() {
    float windowH = 720.0f, windowW = 1024.0f;  // px

    Renderer renderer(windowH, windowW, "4a-engine");
    GLFWwindow* window = renderer.InitWindow();

    char absoluteExePath[256];
    GetCurrentDirectoryA(256, absoluteExePath);
    int absPathLen = strlen(absoluteExePath);

    GlShader shader;
    GLuint shaderProgram;

    #ifdef TEST_BUILD
        absoluteExePath[absPathLen - strlen("build")] = '\0';
    #endif
    std::string absoluteShadersPath = absoluteExePath;
    std::string absoluteResourcePath = absoluteExePath;
    absoluteShadersPath += "shaders\\";
    absoluteResourcePath += "res\\";
    //Load external data form disc
    std::cout << "Loading shaders from " << absoluteShadersPath << std::endl;
    std::cout << "Loading resources from " << absoluteResourcePath << std::endl;
    //Shaders
    shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    //Textures
    std::shared_ptr<Texture> room_tex = std::make_shared<Texture>();
    std::shared_ptr<Texture> hero_tex = std::make_shared<Texture>();
    std::shared_ptr<Texture> hero2_tex = std::make_shared<Texture>();
    room_tex->LoadImage(absoluteResourcePath + "room1.png");
    hero_tex->LoadImage(absoluteResourcePath + "left1.png");
    hero2_tex->LoadImage(absoluteResourcePath + "left2.png");

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
    GameObject room;
    room.SetTexture(room_tex);
    room.SetLayer(LAYER_BG);
    room.SetShaderProgram(shaderProgram);
    
    //Hero
    GameObject hero;
    hero.SetTexture(hero_tex);
    hero.SetLayer(LAYER_HERO);
    hero.SetShaderProgram(shaderProgram);
    hero.Scale({2.9f, 2.5f});

    //Hero 2
    GameObject hero2;
    hero2.SetTexture(hero2_tex);
    hero2.SetLayer(LAYER_HERO);
    hero2.SetShaderProgram(shaderProgram);
    hero2.Scale(2.f);

    //Objects in the scene are no longer cannot be accessed from here
    //To access uploaded object there is a game_object_id
    game_object_id hero_id = scene->UploadObject(hero);
    scene->UploadObject(room);
    game_object_id hero2_id = scene->UploadObject(hero2);
    //OnEvent() function of img_id object will be called 
    //whenever a key event occurs
    ctrl->AddEventListener(scene->GetObjectById(hero_id));
    ctrl->AddEventListener(scene->GetObjectById(hero2_id));

    renderer.SetScene(scene);
    renderer.Start();
    //TODO: сделать вызов glfwTerminate();
}