#define TEST_BUILD
#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

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
        //WaitForSingleObject(mtx, INFINITE);
        ReleaseMutex(mtx);
    }
};

keyHandler wasdHandler(0);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        wasdHandler.setData(GLFW_KEY_A);
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        wasdHandler.setData(GLFW_KEY_W);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        wasdHandler.setData(GLFW_KEY_S);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        wasdHandler.setData(GLFW_KEY_D);
    }
    if (action == GLFW_RELEASE) {
        wasdHandler.setData(0);
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

    //Инициализация GLFW (для создания окна)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Задание версии OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Установка профиля, для которого создается контекст 
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);  // Запрет на изменение размера окна

    //Создание окна
    GLFWwindow* window = glfwCreateWindow(windowW, windowH, "4a game", nullptr, nullptr);
    if (window == nullptr)  // Ошибка
    {
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
    }
    glfwMakeContextCurrent(window);  // Задает контекст окна текущим контекстом для этого потока

    //Инициализация функций OpenGL с помощью GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    //Теперь можно использовать функции OpenGL
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  // Функция из glfw для получения width и height окна window
    glViewport(0, 0, width, height);  // 0,0 - позиция нижнего левого угла окна. Эта величина от 0 до 1 (здесь это будет (0, 720) или (0, 1024))
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

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
        // x,   y,      z,     r,     g,      b,     texture coords
        heroW,  heroH,    0.0f,  1.0f,  0.0f,   0.0f,  1.0f, 1.0f,
        heroW,  0,        0.0f,  0.0f,  1.0f,   0.0f,  1.0f, 0.0f,
        0,      0,        0.0f,  0.0f,  0.0f,   1.0f,  0.0f, 0.0f,
        0,      heroH,    0.0f,  1.0f,  0.0f,   0.0f,  0.0f, 1.0f
    };
    //То же самое, но для фона
    GLfloat verticesRoom[] = {
        // x,   y,      z,     r,     g,      b,     texture coords                                    r      g       b      x     y
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

    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBuffer vb_room(verticesRoom, sizeof(verticesRoom));
    VertexArray va, va_room;
    IndexBuffer ib(indices, sizeof(indices));

    VertexLayout vl(0);
    vl.Push<float>(3);
    vl.Push<float>(3);
    vl.Push<float>(2);

    VertexLayout vl_room(0);
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
    GLuint vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);  // Создаем шейдер с типом VERTEX
    //Надо подгрузить его в С-строку из файла (но сейчас он просто здесь)
    char **vShaderStr = (char**)malloc(2 * sizeof(char*));
    std::string vertexShaderSrc = 
    "#version 330 core \n\
    layout (location = 0) in vec3 position; \n\
    layout (location = 1) in vec3 color; \n\
    layout (location = 2) in vec2 texCoord; \n\
    out vec3 ourColor; \n\
    out vec2 TexCoord; \n\
    uniform int orientation; \n\
    uniform mat4 model; \n\
    uniform int is_transformable; \n\
    uniform mat4 proj; \n\
    uniform mat4 view; \n\
    void main() { \n\
        if (is_transformable == 1) { \n\
            gl_Position = proj * view * model * vec4(position, 1.0f); \n\
        } \n\
        else { \n\
            gl_Position = proj * view * vec4(position, 1.0f); \n\
        } \n\
        TexCoord.y = 1.0f - texCoord.y; \n\
        if (orientation == 1 && is_transformable == 1) { \n\
            TexCoord.x = 1.0f - texCoord.x; \n\
        } \n\
        else { \n\
            TexCoord.x = texCoord.x; \n\
        } \n\
        ourColor = color; \n\
    }";
    vShaderStr[0] = (char*)vertexShaderSrc.c_str();
    //Привязываем исходный код шейдера к объекту шейдера
    glShaderSource(vertex_shader, 1, vShaderStr, NULL); // Здесь 1 - количсество строк
    glCompileShader(vertex_shader);  // Компилируем его
    //Проверим, удачно ли он скомпилился
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        //Печатем в infoLog ошибку
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    } //Если все ок, то вершинный шейдер будет собран

    //Теперь то же самое для фрагментного шейдера
    GLuint fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char **vShaderStrFragment = (char**)malloc(2 * sizeof(char*));
    //Используем заданный программно цвет
    std::string fragmentShaderSrc = 
    "#version 330 core \n\
    in vec3 ourColor; \n\
    in vec2 TexCoord; \n\
    out vec4 color; \n\
    uniform sampler2D ourTexture; \n\
    void main() { \n\
        color = texture(ourTexture, TexCoord); \n\
    }";
    vShaderStrFragment[0] = (char*)fragmentShaderSrc.c_str();
    glShaderSource(fragment_shader, 1, vShaderStrFragment, NULL);
    glCompileShader(fragment_shader);
    memset(infoLog, 0, sizeof(infoLog));
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        //Печатем в infoLog ошибку
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    } //Если все ок, то вершинный шейдер будет собран


    //Теперь нужно собрать шейдерную программу - результат комбинации нескольких шейдеров
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);  // Присоединяем к программе шейдеры (они уже типизированы ранее)
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);  // Связывание шейдеров
    //Проверим успешность сборки программы
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    memset(infoLog, 0, sizeof(infoLog));
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    }
    //После связывыния шейдеры можно удалить
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(vShaderStr[0]);
    free(vShaderStrFragment[0]);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Задаем колбэк - функция при нажатии клавишы
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
    int sceneFramesPerAnim = floor(20 / (float)animationFps);
    int animationFrames = 7 - 1;

    //Добавим возможность трансформации:
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(windowW, windowH, 0.0f));
    Camera orthCam(windowW, windowH);
    glm::mat4 proj = orthCam.GetProj();
    glm::mat4 view;
    glm::vec3 heroGoLeft = glm::vec3(0.0f);
    glm::vec3 heroGoRight = glm::vec3(0.0f);

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

        int currentKeyPressed = wasdHandler.getData();
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
                break;
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
        va_room.Bind();
        vb_room.Bind();
        glUniform1i(glGetUniformLocation(shaderProgram, "is_transformable"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 7);
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
        Sleep(50);  // Чтобы не нагружать карту - ограничение 20 фпс
        framesDrawn = framesDrawn % 20;
        framesDrawn++;
        //std::cout << "framesDrawn: " << framesDrawn << "\n";
    }
    std::cout << "Loop done\n";
    //Очитска выделенных ресурсов
    delete &wasdHandler;
    glfwTerminate();
    std::cout << "glfwTerminate done\n";
    return 0;
}