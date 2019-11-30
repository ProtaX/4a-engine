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

using namespace fae;

static const char* strcatcpy(char* string, const char* catstr) {
    unsigned int stringLen = strlen(string);
    char* newStr = new char[stringLen + strlen(catstr)];
    strcpy(newStr, string);
    strcpy(&newStr[stringLen], catstr);
    return newStr;
}
    
int main() {
    
    //Некоторые данные о размере окна и спрайта
    float windowH = 720.0f, windowW = 1024.0f;  // px
    float heroH = 125, heroW = 75;  // px
    float roomH = 1238, roomW = 2000;

    Renderer renderer(windowH, windowW, "4a-engine");
    GLFWwindow* window = renderer.InitWindow();

    int tex_h, tex_w;
    int room1_h, room1_w;

    char absoluteExePath[256];
    GetCurrentDirectoryA(256, absoluteExePath);
    int absoluteexePathLen = strlen(absoluteExePath);
    
#ifdef TEST_BUILD
    strcpy(&absoluteExePath[absoluteexePathLen - 5], "res\\");
#else
    strcpy(&absoluteExePath[absoluteexePathLen], "\\res\\");
#endif
    std::cout << "Loading resources from " << absoluteExePath << std::endl;
    //TODO: здесь течет память (динамически аллоцируется строка в strcatcpy)
    unsigned char* room1 = SOIL_load_image(strcatcpy(absoluteExePath, "room1.png"), &room1_h, &room1_w, 0, SOIL_LOAD_RGBA);
    unsigned char* image = SOIL_load_image(strcatcpy(absoluteExePath, "left1.png"), &tex_h, &tex_w, 0, SOIL_LOAD_RGBA);
    if (!image || !room1) {
        std::cout << "ERROR::SOIL::IMAGE::LOAD_FAILED\n";
        glfwTerminate();
        return -1;
    }

    GlShader shader;
    GLuint shaderProgram;

    std::string absoluteShadersPath = absoluteExePath;
    #ifdef TEST_BUILD
        absoluteShadersPath += "../shaders/";
    #else
        absoluteShadersPath += "shaders/";
    #endif
    std::cout << "Loading shaders from " << absoluteShadersPath << std::endl;
    shaderProgram = shader.loadFiles (absoluteShadersPath + "vs.glsl", absoluteShadersPath + "fs.glsl");

    //Камера с видом сверху
    std::shared_ptr<Camera> orthCam = std::make_shared<Camera>(windowW, windowH);
    //Сцена, которую будут наполнять объекты
    std::shared_ptr<GameScene> scene = std::make_shared<GameScene>();
    scene->SetCamera(orthCam);
    //Управление с клавиатуры
    KeyboardControl* ctrl = new KeyboardControl(window);

    //Так создается объект
    //Это задний фон
    GameObject room;
    room.SetSize({roomW, roomH});
    room.SetSingleTexture(room1, room1_h, room1_w, GL_TEXTURE7);
    room.SetShaderProgram(shaderProgram);
    
    //Картника поверх заднего фона
    GameObject img;
    img.SetCoords({500.f, 600.f}, {500.f+heroW, 600.f+heroH});
    img.SetSingleTexture(image, tex_h, tex_w, GL_TEXTURE8);
    img.SetShaderProgram(shaderProgram);

    //Добавляем объекты на сцену
    scene->AddObject(room);
    //Получим id Этого объекта внутри сцены, чтобы задать для него управление
    game_object_id img_id = scene->AddObject(img);
    //Задаем возможность управления для этого объекта
    ctrl->PushCallback(scene->GetObjectById(img_id));

    //Говорим рендереру, какую сцену рисовать 
    renderer.SetScene(scene);
    //Запуск рендера
    renderer.Start();
    //TODO: сделать вызов glfwTerminate();
}