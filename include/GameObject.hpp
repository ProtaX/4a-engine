#pragma once

struct GameVertex
{
    float x, y;
    float r, g, b;
    float tex_x, tex_y;
};

typedef struct GameVertex gvx_t;

class GameObject {
private:
    int shader_program;
    gvx_t verticies[4];
public:
    GameObject();

    ~GameObject();

};