#define TEST_BUILD

#include <string.h>
#include <math.h>

#include "Core.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include <GlShader.hpp>

using namespace fae;
<<<<<<< HEAD
=======

>>>>>>> master
class keyHandler {
private:
    int data;
    HANDLE mtx;
public:
    keyHandler(int data) {
        mtx = CreateMutex(NULL, FALSE, NULL);
        if (!mtx) {
            std::cout << "Error creating mutex\n";
        }
        this->data = data;
    }
    void setData(int newData) {
        DWORD res = WaitForSingleObject(mtx, INFINITE);
        if (res == WAIT_OBJECT_0) {
            this->data = newData;
        }
        ReleaseMutex(mtx);
    }
    int getData() {
        int ret = -1;
        DWORD res = WaitForSingleObject(mtx, INFINITE);
        if (res == WAIT_OBJECT_0) {
            ret = this->data;
        }
        ReleaseMutex(mtx);

        return ret;
    }

    ~keyHandler() {
        WaitForSingleObject(mtx, INFINITE);
        CloseHandle(mtx);
    }
};

keyHandler* wasdHandler = new keyHandler(0);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        wasdHandler->setData(GLFW_KEY_A);
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        wasdHandler->setData(GLFW_KEY_W);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        wasdHandler->setData(GLFW_KEY_S);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        wasdHandler->setData(GLFW_KEY_D);
    }
    if (action == GLFW_RELEASE) {
        wasdHandler->setData(0);
    }
}

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

    //Загрузим все спрайты анимации
    int tex_h, tex_w, 
        tex_h1, tex_w1, 
        tex_h2, tex_w2,
        tex_h3, tex_w3,
        tex_h4, tex_w4,
        tex_h5, tex_w5, 
        tex_h6, tex_w6;
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
    unsigned char* left1 = SOIL_load_image(strcatcpy(absoluteExePath, "left2.png"), &tex_h1, &tex_w1, 0, SOIL_LOAD_RGBA);
    unsigned char* left2 = SOIL_load_image(strcatcpy(absoluteExePath, "left3.png"), &tex_h2, &tex_w2, 0, SOIL_LOAD_RGBA);
    unsigned char* left3 = SOIL_load_image(strcatcpy(absoluteExePath, "left4.png"), &tex_h3, &tex_w3, 0, SOIL_LOAD_RGBA);
    unsigned char* left4 = SOIL_load_image(strcatcpy(absoluteExePath, "left5.png"), &tex_h4, &tex_w4, 0, SOIL_LOAD_RGBA);
    unsigned char* left5 = SOIL_load_image(strcatcpy(absoluteExePath, "left6.png"), &tex_h5, &tex_w5, 0, SOIL_LOAD_RGBA);
    unsigned char* left6 = SOIL_load_image(strcatcpy(absoluteExePath, "left7.png"), &tex_h6, &tex_w6, 0, SOIL_LOAD_RGBA);
    if (!image || !left1 || !left2 || !left3 || !left4 || !left5 || !left6 || !room1) {
        std::cout << "ERROR::SOIL::IMAGE::LOAD_FAILED\n";
        glfwTerminate();
        return -1;
    }

    float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};

    GLuint heroAnimation[7];
    glGenTextures(7, heroAnimation);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h, tex_w, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h1, tex_w1, 0, GL_RGBA, GL_UNSIGNED_BYTE, left1);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h2, tex_w2, 0, GL_RGBA, GL_UNSIGNED_BYTE, left2);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h3, tex_w3, 0, GL_RGBA, GL_UNSIGNED_BYTE, left3);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h4, tex_w4, 0, GL_RGBA, GL_UNSIGNED_BYTE, left4);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h5, tex_w5, 0, GL_RGBA, GL_UNSIGNED_BYTE, left5);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, heroAnimation[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h6, tex_w6, 0, GL_RGBA, GL_UNSIGNED_BYTE, left6);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    // Можно убрать спрайты из памяти
    SOIL_free_image_data(image);
    SOIL_free_image_data(left1);
    SOIL_free_image_data(left2);
    SOIL_free_image_data(left3);
    SOIL_free_image_data(left4);
    SOIL_free_image_data(left5);
    SOIL_free_image_data(left6);

    GlShader shader;
    GLuint shaderProgram;

    #ifdef TEST_BUILD
        strcpy(&absoluteExePath[absoluteexePathLen - 5], "shaders\\");
    #else
        strcpy(&absoluteExePath[absoluteexePathLen], "\\shaders\\");
    #endif
    std::cout << "Loading resources from " << absoluteExePath << std::endl;
    std::string absoluteExePath1 = absoluteExePath;
    //std::string absoluteExePath1 = std::string(absoluteExePath);
    std::string vs ="vs.glsl";
    std:: string vertex_file_name=absoluteExePath + vs;
    std::cout<<vertex_file_name<<'\n';
    std::string fs ="fs.glsl";
    std:: string fragment_file_name=absoluteExePath + fs;
    std::cout<<fragment_file_name<<'\n';
    //const char* fragment_file_name=strcatcpy(absoluteExePath, "fs.glsl");
    // std::cout<<vertex_file_name<<'\n'<<fragment_file_name<<'\n';
    shaderProgram = shader.loadFiles (vertex_file_name, fragment_file_name);
    //shaderProgram = shader.loadFiles ("C:/git/4a-engine/shaders/vs.glsl", "C:/git/4a-engine/shaders/fs.glsl");

    //Задаем callback при нажатии на клавиатуру 
    glfwSetKeyCallback(window, key_callback);

    //Камера с видом сверху
    std::shared_ptr<Camera> orthCam = std::make_shared<Camera>(windowW, windowH);
    //Сцена, которую будут наполнять объекты
    std::shared_ptr<GameScene> scene = std::make_shared<GameScene>();
    
    //Так создается объект
    //Это задний фон
    GameObject room;
    room.SetSize({roomW, roomH});
    room.SetSingleTexture(room1, room1_h, room1_w, GL_TEXTURE7);
    room.SetShaderProgram(shaderProgram);
    
    //Картника поверх заднего фона
    GameObject img;
    img.SetCoords({500., 600.}, {600., 700.});
    img.SetSingleTexture(room1, room1_h, room1_w, GL_TEXTURE8);
    img.SetShaderProgram(shaderProgram);

    //Добавляем объекты на сцену
    scene->AddObject(room);
    scene->AddObject(img);
    scene->SetCamera(orthCam);
    //Говорим рендереру, какую сцену рисовать 
    renderer.SetScene(scene);
    //Запуск рендера
    renderer.Start();
    delete wasdHandler;
}