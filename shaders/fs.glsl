#version 330 core \n\
    in vec3 ourColor; \n\
    in vec2 TexCoord; \n\
    out vec4 color; \n\
    uniform sampler2D ourTexture; \n\
    void main() { \n\
        color = texture(ourTexture, TexCoord); \n\
    }