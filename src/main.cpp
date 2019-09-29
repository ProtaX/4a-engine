#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
#include "SOIL.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

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

int main() {
    //Некоторые данные о размере окна и спрайта
    int windowH = 720, windowW = 1024;  // px
    int heroH = 75, heroW = 39;  // px
    int heroCenterH = 0, heroCenterW = 0;

    //Инициализация GLFW (для создания окна)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Задание версии OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Установка профиля, для которого создается контекст 
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // Запрет на изменение размера окна

    //Создание окна
    GLFWwindow* window = glfwCreateWindow(windowW, windowH, "Hello World!", nullptr, nullptr);
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

    //Загрузим все спрайты анимации
    int tex_h, tex_w, 
        tex_h1, tex_w1, 
        tex_h2, tex_w2,
        tex_h3, tex_w3,
        tex_h4, tex_w4,
        tex_h5, tex_w5;
    unsigned char* image = SOIL_load_image("c:\\Users\\karpe\\4a-engine\\res\\left.png" , &tex_h, &tex_w, 0, SOIL_LOAD_RGBA);
    unsigned char* left1 = SOIL_load_image("c:\\Users\\karpe\\4a-engine\\res\\left1.png", &tex_h1, &tex_w1, 0, SOIL_LOAD_RGBA);
    unsigned char* left2 = SOIL_load_image("c:\\Users\\karpe\\4a-engine\\res\\left2.png", &tex_h2, &tex_w2, 0, SOIL_LOAD_RGBA);
    unsigned char* left3 = SOIL_load_image("c:\\Users\\karpe\\4a-engine\\res\\left3.png", &tex_h3, &tex_w3, 0, SOIL_LOAD_RGBA);
    unsigned char* left4 = SOIL_load_image("c:\\Users\\karpe\\4a-engine\\res\\left4.png", &tex_h4, &tex_w4, 0, SOIL_LOAD_RGBA);
    unsigned char* left5 = SOIL_load_image("c:\\Users\\karpe\\4a-engine\\res\\left5.png", &tex_h5, &tex_w5, 0, SOIL_LOAD_RGBA);
    if (!image || !left1 || !left2 || !left3 || !left4 || !left5) {
        std::cout << "ERROR::SOIL::IMAGE::LOAD_FAILED\n";
        glfwTerminate();
        return -1;
    }
    else {
        std::cout << "Image loaded, w: " << tex_w << " , h: " << tex_h << "\n";
    }
    GLuint texture, tex1, tex2, tex3, tex4, tex5;
    float borderColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    //Теперь для каждого спрайта нужно задать настройки
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);  // Активируем текстурный блок и задаем настройки для него
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h, tex_w, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &tex1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h1, tex_w1, 0, GL_RGBA, GL_UNSIGNED_BYTE, left1);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &tex2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h2, tex_w2, 0, GL_RGBA, GL_UNSIGNED_BYTE, left2);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &tex3);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, tex3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h3, tex_w3, 0, GL_RGBA, GL_UNSIGNED_BYTE, left3);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &tex4);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, tex4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h4, tex_w4, 0, GL_RGBA, GL_UNSIGNED_BYTE, left4);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &tex5);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, tex5);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_h5, tex_w5, 0, GL_RGBA, GL_UNSIGNED_BYTE, left5);
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
    glBindTexture(GL_TEXTURE_2D, 0);  // Отвяжем объект текстуры

    //поместим четырехугольник в центр экрана, сохраняя пропорции

    //Набор вершин и цветов для двух тругольников
    //UPD: в текущей версии поля r, g, b не используются
    GLfloat vertices[] = {
        // x,   y,      z,     r,     g,      b,     texture coords
        ((float)(heroCenterW + (heroW))/windowW),  ((float)(heroCenterH + (heroH ))/windowH),  0.0f,  1.0f,  0.0f,   0.0f,  1.0f, 1.0f,
        ((float)(heroCenterW + (heroW ))/windowW),  ((float)(heroCenterH - (heroH ))/windowH),  0.0f,  0.0f,  1.0f,   0.0f,  1.0f, 0.0f,
        ((float)(heroCenterW - (heroW ))/windowW),  ((float)(heroCenterH - (heroH ))/windowH),  0.0f,  0.0f,  0.0f,   1.0f,  0.0f, 0.0f,
        ((float)(heroCenterW - (heroW ))/windowW),  ((float)(heroCenterH + (heroH ))/windowH),  0.0f,  1.0f,  0.0f,   0.0f,  0.0f, 1.0f
    };
    //Порядок, в котором надо нарисовать из них треугольники
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    GLuint VBO;  // Идентификатор VBO
    glGenBuffers(1, &VBO);  // Создать буффер и привязать к нему id
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Привязать буффер VBO (уже готовый) к типу GL_ARRAY_BUFFER (далее используется только тип буффера)

    //Далее можно создать объект IBO - index buffer object
    //Отрисовка из этого буффера будет использовать только индексы, а данные будет брать из 
    //GL_ARRAY_BUFFER
    //IBO учитывет разметку VBO
    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Теперь создадим VAO - он позволит хранить в себе все вершинные аттрибуты для заданных VBO
    //VAO содержит в себе: вызов glEnableVertexAttribArray; конфигурацию glVertexAttribPointer; ассоциированные с аттрибутами VBO по glVertexAttribPointer
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Теперь скопируем данные о вершинах в этот буффер
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Записать в буффер, привязанный к типу GL_ARRAY_BUFFER данные в режиме GL_STATIC_DRAW
    //GL_STATIC_DRAW - значит, данные редко или никогда не будут изменяться, аналогично -> DYNAMIC -> STREAM.

    //Пока что OpenGL не знает, как передать данные в аттрибуты вершинного шейдера
    //Теперь нужно задать разметку и тип аттрибутов вершинного шейдера
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT))); //0 - номер аттрибута, который надо настроить. его указали явно строкой layout: (location = 0), 
    // то есть, аттрибут location будет под номером 0; далее: 3 - размер аргумента в шейдере (vec3); внутри vec3 используется GL_FLOAT; GL_FALSE - надо ли нормализировать входные данные;
    // шаг, т.е. расстояние между наборами данных (можно автоматически); (GLvoid*)0 - смещение начала данных в буффере
    glEnableVertexAttribArray(0);  // Включаем аттрибут с номером 0
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    

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
    void main() { \n\
        gl_Position = vec4(position, 1.0f); \n\
        TexCoord.y = 1.0f - texCoord.y; \n\
        if (orientation == 1) { \n\
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
    vShaderStrFragment[1] = (char*)fragmentShaderSrc.c_str();
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Задаем колбэк - функция при нажатии клавишы
    glfwSetKeyCallback(window, key_callback);
    //Начальный спрайт анимации
    int currentGlTexture = GL_TEXTURE0;
    //Зададим количество кадров анимации в секунду
    int animationFps = 10;
    //Состояние анимации - происходит и, если да, какая
    int animationState = 0;
    //Сколько кадров уже было отрисовано
    int framesDrawn = 1;
    //Для кажой отдельной анимации считается: сколько экранных кадров будут рисовать один кадр анимации
    int sceneFramesPerAnim = floor(20 / (float)animationFps);
    //Теперь это можно отрисовывать в игровом цикле
    //Цикл, который держит окно, пока его не закроют
    while(!glfwWindowShouldClose(window))
    {
        //Теперь можно исользовать созданную программу
        GLint orientationLocation = glGetUniformLocation(shaderProgram, "orientation");
        glUseProgram(shaderProgram);
        glfwPollEvents();  // Проверяет события (как ввод с клавиатуры) и дергает соответсвующие callback`и

        //TODO: разобраться с возможной потерей 6-го кадра
        int currentKeyPressed = wasdHandler.getData();
        std::cout << "Current key pressed: " << currentKeyPressed << "\n";
        std::cout << "(framesDrawn % sceneFramesPerAnim) " << (framesDrawn % sceneFramesPerAnim) << "\n";
        
        //Этот большой блок if-else можно запихнуть в функцию и передавать туда адрес currentGlTexture
        if (!(framesDrawn % sceneFramesPerAnim) && currentKeyPressed) {  // Если нажата кнопка и текущий кадр подходит по времени для отрисовки спрайта
            switch (animationState) {
                case GLFW_KEY_A:
                    //Изменяем поворот спрайта и отрисовываем следующий кадр
                    if (currentKeyPressed == GLFW_KEY_D) {
                        //Изменяем поворот спрайта и отрисовываем следующий кадр
                        glUniform1i(orientationLocation, 1);
                        currentGlTexture = GL_TEXTURE0;
                        animationState = 0;
                        break;
                    } 
                    glUniform1i(orientationLocation, -1);
                    if (currentGlTexture - GL_TEXTURE0 >= 4)
                        currentGlTexture = GL_TEXTURE0;
                    else
                        currentGlTexture ++;
                    std::cout << "currentGlTexture: " << currentGlTexture - GL_TEXTURE0 << "\n"; 
                break;
                case GLFW_KEY_D:
                    if (currentKeyPressed == GLFW_KEY_A) {
                        //Изменяем поворот спрайта и отрисовываем следующий кадр
                        glUniform1i(orientationLocation, -1);
                        currentGlTexture = GL_TEXTURE0;
                        animationState = 0;
                        break;
                    } 
                    //Аналогично
                    glUniform1i(orientationLocation, 1);
                    if (currentGlTexture - GL_TEXTURE0 >= 4)
                        currentGlTexture = GL_TEXTURE0;
                    else
                        currentGlTexture ++;
                    std::cout << "currentGlTexture: " << currentGlTexture - GL_TEXTURE0 << "\n";
                break;
                default:  // Анимация не происходит
                    animationState = currentKeyPressed;  // Запустим анимацию
                    currentGlTexture = GL_TEXTURE0;  // С начала
                break;
            }
        }
        else if (!(framesDrawn % sceneFramesPerAnim)) {
            switch (animationState) {
                case GLFW_KEY_A:
                    //Изменяем поворот спрайта и отрисовываем следующий кадр
                    glUniform1i(orientationLocation, -1);
                    if (currentGlTexture - GL_TEXTURE0 >= 4) {
                        currentGlTexture = GL_TEXTURE0;
                        animationState = 0;
                    }
                    else
                        currentGlTexture ++;
                    std::cout << "currentGlTexture: " << currentGlTexture - GL_TEXTURE0 << "\n"; 
                break;
                case GLFW_KEY_D:
                    glUniform1i(orientationLocation, 1);
                    if (currentGlTexture - GL_TEXTURE0 >= 4) {
                        currentGlTexture = GL_TEXTURE0;
                        animationState = 0;
                    }
                    else
                        currentGlTexture ++;
                    std::cout << "currentGlTexture: " << currentGlTexture - GL_TEXTURE0 << "\n"; 
                break;
                default:  // Анимация не происходит
                    currentGlTexture = GL_TEXTURE0;
                break;
            }
        }

        glBindVertexArray(VAO);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), currentGlTexture - GL_TEXTURE0);  // Спрайт рисуется
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);  // Используем IBO для отрисовки квадрата, внутри которого будет текстура
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);  // Заменяет цветовой буфер на подготовленный и показывает его в окне (см. двойная буферизация)
        Sleep(50);  // Чтобы не нагружать карту - ограничение 20 фпс
        framesDrawn = framesDrawn % 20;
        framesDrawn++;
        std::cout << "framesDrawn: " << framesDrawn << "\n";
    }

    //Очитска выделенных ресурсов
    glfwTerminate();
    return 0;
}