//TODO: cmake glew
#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

#include <iostream>
#include <stdlib.h>

int main() {
    //Инициализация GLFW (для создания окна)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Установка профиля, для которого создается контекст 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // Запрет на изменение размера окна

    //Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
    }
    glfwMakeContextCurrent(window);

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

    //Цикл, которые держит окно, пока его не закроют
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();  // Проверяет событыя (как ввод с клавиатуры) и дергает соотв-е callback`и
        glfwSwapBuffers(window);  // Заменяет цветовой буфер на подготовленный и показывает его в окне (см. двойная буферизация)
    }

    //Очитска вфделенных ресурсов
    glfwTerminate();
    return 0;
}