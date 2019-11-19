#define TEST_BUILD

#include <SOIL.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Core.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include <GlShader.hpp>

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

    

       
  GlShader shader;    
int main() {
    
    //Некоторые данные о размере окна и спрайта
    float windowH = 720.0f, windowW = 1024.0f;  // px
    float heroH = 125, heroW = 75;  // px
    float roomH = 1238, roomW = 2000;

    fae::Renderer renderer(windowH, windowW, "4a-engine", 0);
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

    GLuint heroAnimation[7];
    float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    //Текстура для пола комнаты
    GLuint room_tex;
    glGenTextures(1, &room_tex);
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, room_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, room1_h, room1_w, 0, GL_RGBA, GL_UNSIGNED_BYTE, room1);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

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
    SOIL_free_image_data(room1);
    glBindTexture(GL_TEXTURE_2D, 0);  // Отвяжем объект текстуры

    //поместим четырехугольник в центр экрана, сохраняя пропорции

    //Набор вершин и цветов для двух тругольников
    //UPD: в текущей версии поля r, g, b не используются
    GLfloat vertices[] = {
        // x,   y,       z,      r,     g,      b,     texture coords
        heroW,  heroH,    0.0f,  1.0f,  0.0f,   0.0f,  1.0f, 1.0f,
        heroW,  0,        0.0f,  0.0f,  1.0f,   0.0f,  1.0f, 0.0f,
        0,      0,        0.0f,  0.0f,  0.0f,   1.0f,  0.0f, 0.0f,
        0,      heroH,    0.0f,  1.0f,  0.0f,   0.0f,  0.0f, 1.0f
    };
    //То же самое, но для фона
    GLfloat verticesRoom[] = {
        roomW,  roomH,    0.0f,  1.0f,  0.0f,   0.0f,  1.0f, 1.0f,
        roomW,  0,        0.0f,  0.0f,  1.0f,   0.0f,  1.0f, 0.0f,
        0,      0,        0.0f,  0.0f,  0.0f,   1.0f,  0.0f, 0.0f,
        0,       roomH,   0.0f,  1.0f,  0.0f,   0.0f,  0.0f, 1.0f
    };
    //Порядок, в котором надо нарисовать из них треугольники
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    fae::VertexBuffer vb(vertices, sizeof(vertices));
    fae::VertexBuffer vb_room(verticesRoom, sizeof(verticesRoom));
    fae::VertexArray va, va_room;
    fae::IndexBuffer ib(indices, sizeof(indices));
    fae::Camera orthCam(windowW, windowH);

    fae::VertexLayout vl;
    vl.Push<float>(3);
    vl.Push<float>(3);
    vl.Push<float>(2);

    fae::VertexLayout vl_room;
    vl_room.Push<float>(3);
    vl_room.Push<float>(3);
    vl_room.Push<float>(2);    

    va.Bind();
    ib.Bind();
    va.AddBuffer(vb, vl);
    va.Unbind();

    va_room.Bind();
    ib.Bind();
    va_room.AddBuffer(vb_room, vl_room);
    va_room.Unbind();

    //Теперь нужно подключить шейдеры
    


    





//   //oldkod
//     vertex_shader = glCreateShader(GL_VERTEX_SHADER);  // Создаем шейдер с типом VERTEX
//     //Надо подгрузить его в С-строку из файла (но сейчас он просто здесь)
//     char **vShaderStr = (char**)malloc(2 * sizeof(char*));
//     std::string vertexShaderSrc = 
//     "#version 330 core \n\
//     layout (location = 0) in vec3 position; \n\
//     layout (location = 1) in vec3 color; \n\
//     layout (location = 2) in vec2 texCoord; \n\
//     out vec3 ourColor; \n\
//     out vec2 TexCoord; \n\
//     uniform int orientation; \n\
//     uniform mat4 model; \n\
//     uniform int is_transformable; \n\
//     uniform mat4 proj; \n\
//     uniform mat4 view; \n\
//     void main() { \n\
//         if (is_transformable == 1) { \n\
//             gl_Position = proj * view * model * vec4(position, 1.0f); \n\
//         } \n\
//         else { \n\
//             gl_Position = proj * view * vec4(position, 1.0f); \n\
//         } \n\
//         TexCoord.y = 1.0f - texCoord.y; \n\
//         if (orientation == 1 && is_transformable == 1) { \n\
//             TexCoord.x = 1.0f - texCoord.x; \n\
//         } \n\
//         else { \n\
//             TexCoord.x = texCoord.x; \n\
//         } \n\
//         ourColor = color; \n\
//     }";
//     vShaderStr[0] = (char*)vertexShaderSrc.c_str();
//     //Привязываем исходный код шейдера к объекту шейдера
//     glShaderSource(vertex_shader, 1, vShaderStr, NULL); // Здесь 1 - количсество строк
//     glCompileShader(vertex_shader);  // Компилируем его
//     //Проверим, удачно ли он скомпилился
//     GLint success;
//     GLchar infoLog[512];
//     glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         //Печатем в infoLog ошибку
//         glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
// 	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//         glfwTerminate();
//         return -1;
//     } //Если все ок, то вершинный шейдер будет собран

//     //Теперь то же самое для фрагментного шейдера
//     GLuint fragment_shader;
//     fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//     char **vShaderStrFragment = (char**)malloc(2 * sizeof(char*));
//     //Используем заданный программно цвет
//     std::string fragmentShaderSrc = 
//     "#version 330 core \n\
//     in vec3 ourColor; \n\
//     in vec2 TexCoord; \n\
//     out vec4 color; \n\
//     uniform sampler2D ourTexture; \n\
//     void main() { \n\
//         color = texture(ourTexture, TexCoord); \n\
//     }";
//     vShaderStrFragment[0] = (char*)fragmentShaderSrc.c_str();
//     glShaderSource(fragment_shader, 1, vShaderStrFragment, NULL);
//     glCompileShader(fragment_shader);
//     memset(infoLog, 0, sizeof(infoLog));
//     glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         //Печатем в infoLog ошибку
//         glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
// 	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//         glfwTerminate();
//         return -1;
//     } //Если все ок, то вершинный шейдер будет собран

//     //Теперь нужно собрать шейдерную программу - результат комбинации нескольких шейдеров
//     GLuint shaderProgram;
//     shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertex_shader);  // Присоединяем к программе шейдеры (они уже типизированы ранее)
//     glAttachShader(shaderProgram, fragment_shader);
//     glLinkProgram(shaderProgram);  // Связывание шейдеров
//     //Проверим успешность сборки программы
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     memset(infoLog, 0, sizeof(infoLog));
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     //После связывыния шейдеры можно удалить
//     glDeleteShader(vertex_shader);
//     glDeleteShader(fragment_shader);
//     free(vShaderStr[0]);
//     free(vShaderStrFragment[0]);
//     //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint shaderProgram;
    shaderProgram = shader.loadFiles ("C:/git/4a-engine/shaders/vs.glsl", "C:/git/4a-engine/shaders/fs.glsl");
    glfwSetKeyCallback(window, key_callback);
    //Начальный спрайт анимации
    int currentGlTexture = GL_TEXTURE1;
    //Зададим количество кадров анимации в секунду
    int animationFps = 10;
    //Состояние анимации - происходит и, если да, какая
    int animationState = 0;
    //Сколько кадров уже было отрисовано
    int framesDrawn = 1;
    //Для кажой отдельной анимации считается: сколько экранных кадров будут рисовать один кадр анимации
    int sceneFramesPerAnim = floor(144 / (float)animationFps);
    int animationFrames = 7 - 1;

    //Добавим возможность трансформации:
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(windowW, windowH, 0.0f));
    glm::mat4 proj = orthCam.GetProj();
    glm::mat4 view;
    glm::vec3 heroGoLeft = glm::vec3(0.0f);
    glm::vec3 heroGoRight = glm::vec3(0.0f);
    glm::vec3 cameraMoveUp = glm::vec3(0.0f,   -heroW /  animationFrames, 0.0f);
    glm::vec3 cameraMoveDown = glm::vec3(0.0f, heroW /  animationFrames, 0.0f);

    //Размещение всех unform
    GLint orientationLocation, modelLocation, projLocation, veiwLocation;

    //Теперь это можно отрисовывать в игровом цикле
    //Цикл, который держит окно, пока его не закроют

    while(!glfwWindowShouldClose(window))
    {
        glUseProgram(shaderProgram);
        glClear(GL_COLOR_BUFFER_BIT);
        view = orthCam.GetVeiw();

        //Теперь можно исользовать созданную программу
        orientationLocation = glGetUniformLocation(shaderProgram, "orientation");
        projLocation = glGetUniformLocation(shaderProgram, "proj");
        modelLocation = glGetUniformLocation(shaderProgram, "model");
        veiwLocation = glGetUniformLocation(shaderProgram, "view");

        heroGoLeft[0] = - heroW /  animationFrames;
        heroGoRight[0] = heroW  / animationFrames;

        //Трансформация
        GLCall(glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj)));
        GLCall(glUniformMatrix4fv(veiwLocation, 1, GL_FALSE, glm::value_ptr(view)));
        GLCall(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model)));  // 1- сколько матриц отправляем, GL_FALSE - надо ли траспонировать
        glfwPollEvents();  // Проверяет события (как ввод с клавиатуры) и дергает соответсвующие callback`и

        int currentKeyPressed = wasdHandler->getData();
        //std::cout << "Current key pressed: " << currentKeyPressed << "\n";
        //std::cout << "(framesDrawn % sceneFramesPerAnim) " << (framesDrawn % sceneFramesPerAnim) << "\n";
        
        //Этот большой блок if-else можно запихнуть в функцию и передавать туда адрес currentGlTexture
        if (!(framesDrawn % sceneFramesPerAnim) && currentKeyPressed) {  // Если нажата кнопка и текущий кадр подходит по времени для отрисовки спрайта
            switch (animationState) {
                case GLFW_KEY_A:
                    //Изменяем поворот спрайта и отрисовываем следующий кадр
                    if (currentKeyPressed == GLFW_KEY_D) {
                        //Изменяем поворот спрайта и отрисовываем следующий кадр
                        glUniform1i(orientationLocation, 1);
                        currentGlTexture = GL_TEXTURE1;
                        animationState = 0;
                        break;
                    } 
                    glUniform1i(orientationLocation, -1);
                    if (currentGlTexture - GL_TEXTURE0 >= animationFrames)
                        currentGlTexture = GL_TEXTURE1;
                    else
                        currentGlTexture ++;
                    model = glm::translate(model, heroGoLeft);
                    orthCam.MoveCamera(heroGoRight);
                break;
                case GLFW_KEY_D:
                    if (currentKeyPressed == GLFW_KEY_A) {
                        //Изменяем поворот спрайта и отрисовываем следующий кадр
                        glUniform1i(orientationLocation, -1);
                        currentGlTexture = GL_TEXTURE1;
                        animationState = 0;
                        break;
                    } 
                    //Аналогично
                    glUniform1i(orientationLocation, 1);
                    if (currentGlTexture - GL_TEXTURE0 >= animationFrames)
                        currentGlTexture = GL_TEXTURE1;
                    else
                        currentGlTexture ++;
                    model = glm::translate(model, heroGoRight);
                    orthCam.MoveCamera(heroGoLeft);
                break;
                default:  // Анимация не происходит
                    animationState = currentKeyPressed;  // Запустим анимацию
                    currentGlTexture = GL_TEXTURE1;  // С начала
                    //orthCam.MoveCamera(cameraStop);
                break;
            }
            if (currentKeyPressed == GLFW_KEY_W) {
                animationState = 0;
                orthCam.MoveCamera(cameraMoveUp);
            }
            if (currentKeyPressed == GLFW_KEY_S) {
                animationState = 0;
                orthCam.MoveCamera(cameraMoveDown);
            }
        }
        else if (!(framesDrawn % sceneFramesPerAnim)) {
            switch (animationState) {
                case GLFW_KEY_A:
                    //Изменяем поворот спрайта и отрисовываем следующий кадр
                    glUniform1i(orientationLocation, -1);
                    if (currentGlTexture - GL_TEXTURE0 >= animationFrames) {
                        currentGlTexture = GL_TEXTURE1;
                        animationState = 0;
                    }
                    else
                        currentGlTexture ++;
                    model = glm::translate(model, heroGoLeft);
                    orthCam.MoveCamera(heroGoRight);
                break;
                case GLFW_KEY_D:
                    glUniform1i(orientationLocation, 1);
                    if (currentGlTexture - GL_TEXTURE0 >= animationFrames) {
                        currentGlTexture = GL_TEXTURE1;
                        animationState = 0;
                    }
                    else
                        currentGlTexture ++;
                    model = glm::translate(model, heroGoRight);
                    orthCam.MoveCamera(heroGoLeft);
                break;
                default:  // Анимация не происходит
                    currentGlTexture = GL_TEXTURE1;
                break;
            }
        }
        

        //back
        glUniform1i(glGetUniformLocation(shaderProgram, "is_transformable"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 7);
        va_room.Bind();
        vb_room.Bind();
        ib.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        va_room.Unbind();
        
        //hero
        va.Bind();
        vb.Bind();
        GLCall(glUniform1i(glGetUniformLocation(shaderProgram, "is_transformable"), 1));
        GLint tex_loc = glGetUniformLocation(shaderProgram, "ourTexture");
        GLCall(glUniform1i(tex_loc, currentGlTexture - GL_TEXTURE0 - 1));  // Спрайт рисуется
        ib.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        va.Unbind();

        glfwSwapBuffers(window);  // Заменяет цветовой буфер на подготовленный и показывает его в окне (см. двойная буферизация)
        framesDrawn = framesDrawn % 144;
        framesDrawn++;
        //std::cout << "framesDrawn: " << framesDrawn << "\n";
    }
    std::cout << "Loop done\n";
    //Очитска выделенных ресурсов
    delete wasdHandler;
    std::cout << "glfwTerminate done\n";
    return 0;
}