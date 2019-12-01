#include "Texture.hpp"

namespace fae {

bool Texture::LoadImage(const std::string& path) {
        pixel_data = SOIL_load_image(path.c_str(), &h, &w, 0, m_force_channels);
        target = vaccant_tex_target;
        if (!pixel_data)
            return false;
        float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
        GLCall(glGenTextures(1, &id));
        GLCall(glActiveTexture(vaccant_tex_target++));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, h, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data));
        GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        return true;
}

Texture::~Texture() {
        if (pixel_data)
            SOIL_free_image_data(pixel_data);
        GLCall(glDeleteTextures(1, &id));
    }

}