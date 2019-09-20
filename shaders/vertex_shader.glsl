#version 330 core

//in vec3 - значит, что входные данные - вектор из 3-х компонент
//layout устанавливает 
layout (location = 0) in vec3 position;


void main() {
    //эта переменная предопределена и ей надо утсановить значение, чтобы шейдер заработал
    gl_Position = vec4(position.x, position.y, position.x, 1.0);
}