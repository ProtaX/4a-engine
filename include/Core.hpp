#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <iostream>
#include <memory>
#include <string>
#include <SOIL.h>

//Фуцнкия, обернутая в этот макро, не может вернуть занчение
#define GLCall(x) \
        x; \
        glGetErrors(__LINE__, __FILE__); \
        glClearErrors() \

#define GLFWCall(x) \
        x; \
        do { \
            const char* errMsg; \
            const char** errMsgLoc = &errMsg; \
            int code = glfwGetError(errMsgLoc); \
            if (code != GLFW_NO_ERROR) { \
                std::cout << "GLFW error: " << errMsg << std::endl; \
                glfwTerminate(); \
            } \
        } while (0) \

void glGetErrors(int line, const char* file);

void glClearErrors();

namespace fae {

typedef struct {
    float x, y;
}point2_t;

typedef struct {
    float x, y, z;
}point3_t;

typedef struct {
    float r, g, b;
}color_t;

}