#include "Texture.hpp"

namespace fae {

Texture::Texture(const std::string& path, int force_channels) {
  m_force_channels_ = force_channels;
  LoadImage(path);
}

bool Texture::LoadImage(const std::string& path) {
    pixel_data_ = SOIL_load_image(path.c_str(), &w, &h, 0, m_force_channels_);
    target_ = VACCANT_TEX_TARGET;
    if (!pixel_data_)
      return false;
    float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLCall(glGenTextures(1, &id_));
    GLCall(glActiveTexture(VACCANT_TEX_TARGET++));
    GLCall(glBindTexture(GL_TEXTURE_2D, id_));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data_));
    GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    return true;
}

Texture::~Texture() {
  if (pixel_data_)
    SOIL_free_image_data(pixel_data_);
  GLCall(glDeleteTextures(1, &id_));
  std::cout << "[~] Texture " << id_ << std::endl;
}

Texture::Texture(int force_channels) noexcept:
        m_force_channels_(force_channels),
        pixel_data_(nullptr),
        h(0),
        w(0),
        target_(GL_TEXTURE0) { }

int Texture::GetH() const { return h; }

int Texture::GetW() const { return w; }

rgba_t * Texture::GetPixelData() const { return pixel_data_; }

GLuint Texture::GetTargetN() const { return target_ - GL_TEXTURE0; }

void Texture::SetForceChannels(int force_channels) { m_force_channels_ = force_channels; }

}  // namespace fae
