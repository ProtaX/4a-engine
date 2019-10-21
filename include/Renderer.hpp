#pragma once

#include "glew.h"
#include <iostream>
#include "Settings.hpp"

#define GLCall(x) \
        GLClearErrors(); \
        x; \
        GLGetErrors(__LINE__) \

void GLClearErrors();

void GLGetErrors(int line) ;

/*
class Renderer {
private:
    Settings settings;
public:
    Renderer() { }

    void InitWindow() {

    }

    void Reset() {

    }

    ~Renderer() { }
    
};*/