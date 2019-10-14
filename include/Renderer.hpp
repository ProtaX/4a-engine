#pragma once

#include "glew.h"
#include <iostream>

#define GLCall(x) \ 
        x; \ 
        GLGetErrors(__LINE__) \ 

void GLGetErrors(int line) ;