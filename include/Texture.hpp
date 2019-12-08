#pragma once

#include "Core.hpp"

namespace fae {

//TODO: сейчас каждая текстура находится в отдельном блоке,
//надо добавить поддержку скрепляемых текстур
class Texture {
private:
    //Свободный текстурный блок
    static GLuint vaccant_tex_target;

    int m_force_channels;
    rgba_t* pixel_data;
    int h, w;
    GLuint id;
    GLuint target;

public:
    Texture(int force_channels = RGBA_TEXTURE):
        m_force_channels(force_channels),
        pixel_data(nullptr),
        h(0),
        w(0),
        target(GL_TEXTURE0)
        { }
    Texture(const std::string& path, int force_channels = RGBA_TEXTURE);
    ~Texture();

    bool LoadImage(const std::string& path);

    inline int GetH() const { return h; }
    inline int GetW() const { return w; }
    inline GLuint GetTargetN() const { return target - GL_TEXTURE0; }
    inline rgba_t* GetPixelData() const { return pixel_data; }
    inline void ForceChannels(int force_channels) { m_force_channels = force_channels; }

};

}