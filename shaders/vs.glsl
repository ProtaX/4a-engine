#version 330 core 
    layout (location = 0) in vec3 position; 
    layout (location = 1) in vec3 color; 
    layout (location = 2) in vec2 texCoord; 
    out vec3 ourColor; 
    out vec2 TexCoord; 
    uniform mat4 model; 
    uniform mat4 proj; 
    uniform mat4 view; 
    void main() { 
        gl_Position = proj * view * model * vec4(position, 1.0f); 
        TexCoord.y = 1.0f - texCoord.y;
        TexCoord.x = texCoord.x;
        ourColor = color;
    }