#include "Engine.hpp"

using namespace fae;

void game() {
    Renderer_p renderer = CreateRenderer(250, 150, "piaps-lab4: Proxy Pattern");

    // Shaders
    GlShader shader;
    std::string absoluteShadersPath = GetWorkingDirectory() + "\\shaders\\";
    GLuint shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");
    
    // Load textures and animations
    std::string absoluteResourcePath = GetWorkingDirectory() + "\\res\\";
    ImageProxy_p proxy = CreateImageProxy(absoluteResourcePath + "idle_static.png");

    // Image
    StaticGameObject_p image = CreateStaticGameObject();
    image->SetTexture(proxy);
    image->SetLayer(LAYER_BG);
    image->Scale({150, 250});
    image->SetShaderProgram(shaderProgram);

    // Set up scene
    GameScene_p scene = CreateGameScene();
    Camera_p orthCam = CreateCamera(250, 150);
    scene->SetCamera(orthCam);
    scene->AddObject(image);

    // Set up window
    renderer->SetIcon(proxy);
    renderer->AddFrameListener(orthCam);  // For smooth camera
    renderer->AddKeyListener(proxy);

    renderer->SetScene(scene);
    renderer->Start();
}