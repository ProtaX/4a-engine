#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <SOIL.h>
#include <stdlib.h>

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

#define RGBA_TEXTURE SOIL_LOAD_RGBA
#define LAYER_BG (0.f)
#define LAYER_HERO (0.1f)

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

typedef unsigned long int game_object_id;

typedef unsigned char rgba_t;

//All classes that are to use callbacks
struct AppInfo {
    void* p_kb_ctl;
};

}