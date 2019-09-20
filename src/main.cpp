#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

int main() {
    //Инициализация GLFW (для создания окна)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Задание версии OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Установка профиля, для которого создается контекст 
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // Запрет на изменение размера окна

    //Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", nullptr, nullptr);
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
    glViewport(0, 0, width, height);  // 0,0 - позиция нижнего левого угла окна. Эта величина от 0 до 1 (здесь это будет (0, 600) или (0, 800))

    //Набор вершин для тругольника
    GLfloat vertices[] = {
        // x, y, z
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f
    };

    GLuint VBO;  // Идентификатор VBO
    glGenBuffers(1, &VBO);  // Создать буффер и привязать к нему id
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Привязать буффер VBO (уже готовый) к типу GL_ARRAY_BUFFER (далее используется только тип буффера)

    //Теперь создадим VAO - он позволит хранить в себе все вершинные аттрибуты для заданных VBO
    //VAO содержит в себе: вызов glEnableVertexAttribArray; конфигурацию glVertexAttribPointer; ассоциированные с аттрибутами VBO по glVertexAttribPointer
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Теперь скопируем данные о вершинах в этот буффер
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Записать в буффер, привязанный к типу GL_ARRAY_BUFFER данные в режиме GL_STATIC_DRAW
    //GL_STATIC_DRAW - значит, данные редко или никогда не будут изменяться, аналогично -> DYNAMIC -> STREAM.

    //Теперь нужно подключить шейдеры
    GLuint vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);  // Создаем шейдер с типом VERTEX
    //Надо подгрузить его в С-строку из файла (но сейчас он просто здесь)
    char **vShaderStr = (char**)malloc(2 * sizeof(char*));
    vShaderStr[0] = strdup("#version 330 core \
layout (location = 0) in vec3 position; \
void main() { gl_Position = vec4(position.x, position.y, position.x, 1.0); }");
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
    vShaderStrFragment[1] = strdup("#version 330 core \
out vec4 color; \
void main() { color = vec4(1.0f, 0.5f, 0.2f, 1.0f); }");
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

    //Пока что OpenGL не знает, как передать данные в аттрибуты вершинного шейдера
    //Теперь нужно задать разметку и тип аттрибутов вершинного шейдера
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0); //0 - номер аттрибута, который надо настроить. его указали явно строкой layout: (location = 0), 
    // то есть, аттрибут location будет под номером 0; далее: 3 - размер аргумента в шейдере (vec3); внутри vec3 используется GL_FLOAT; GL_FALSE - надо ли нормализировать входные данные;
    // шаг, т.е. расстояние между наборами данных (можно автоматически); (GLvoid*)0 - смещение начала данных в буффере
    glEnableVertexAttribArray(0);  // Включаем аттрибут с номером 0


    //Теперь это можно отрисовывать в игровом цикле

    //Цикл, который держит окно, пока его не закроют
    while(!glfwWindowShouldClose(window))
    {
        //Теперь можно исользовать созданную программу
        glUseProgram(shaderProgram);
        glfwPollEvents();  // Проверяет события (как ввод с клавиатуры) и дергает соответсвубщие callback`и
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);  // Заменяет цветовой буфер на подготовленный и показывает его в окне (см. двойная буферизация)
        glBindVertexArray(0);
    }

    //Очитска выделенных ресурсов
    glfwTerminate();
    return 0;
}