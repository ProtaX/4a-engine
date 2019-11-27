#version 330 core 
    layout (location = 0) in vec3 position; 
    layout (location = 1) in vec3 color; 
    layout (location = 2) in vec2 texCoord; 
    out vec3 ourColor; 
    out vec2 TexCoord; 
    uniform int orientation; 
    uniform mat4 model; 
    uniform int is_transformable; 
    uniform mat4 proj; 
    uniform mat4 view; 
    void main() { 
        if (is_transformable == 1) { 
            gl_Position = proj * view * model * vec4(position, 1.0f); 
        } 
        else { 
            gl_Position = proj * view * vec4(position, 1.0f); 
        } 
        TexCoord.y = 1.0f - texCoord.y; 
        if (orientation == 1 && is_transformable == 1) { 
            TexCoord.x = 1.0f - texCoord.x; 
        }
        else { 
            TexCoord.x = texCoord.x; 
        } 
        ourColor = color; 
    }