#define TEST_BUILD

#include <string.h>
#include <math.h>

#include "Core.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "KeyboardControl.hpp"

using namespace fae;

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
    SOIL_free_image_data(left1);
    SOIL_free_image_data(left2);
    SOIL_free_image_data(left3);
    SOIL_free_image_data(left4);
    SOIL_free_image_data(left5);
    SOIL_free_image_data(left6);

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

    //Задаем callback при нажатии на клавиатуру 
    

    //Камера с видом сверху
    std::shared_ptr<Camera> orthCam = std::make_shared<Camera>(windowW, windowH);
    //Сцена, которую будут наполнять объекты
    std::shared_ptr<GameScene> scene = std::make_shared<GameScene>();
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
    img.SetCoords({500., 600.}, {500.+heroW, 600.+heroH});
    img.SetSingleTexture(image, tex_h, tex_w, GL_TEXTURE8);
    img.SetShaderProgram(shaderProgram);
    //Задаем возможность управления для этого объекта
    ctrl->PushCallback(&img);

    //Добавляем объекты на сцену
    scene->AddObject(room);
    scene->AddObject(img);
    scene->SetCamera(orthCam);
    //Говорим рендереру, какую сцену рисовать 
    renderer.SetScene(scene);
    //Запуск рендера
    renderer.Start();
    
    delete wasdHandler;
    //TODO: сделать вызов glfwTerminate();
}