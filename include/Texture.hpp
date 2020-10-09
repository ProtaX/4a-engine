#pragma once

#include <string>
#include <utility>
#include <memory>

#include "Core.hpp"

namespace fae {

class Texture {
 public:
  explicit Texture(int force_channels = RGBA_TEXTURE) noexcept:
    m_force_channels_(force_channels),
    pixel_data_(nullptr),
    h(0),
    w(0),
    target_(GL_TEXTURE0) { }

  explicit Texture(const std::string& path, int force_channels = RGBA_TEXTURE);

  virtual ~Texture();

  bool LoadImage(const std::string& path);

  [[nodiscard]] int GetH() const { return h; }
  [[nodiscard]] int GetW() const { return w; }
  [[nodiscard]] GLuint GetTargetN() const { return target_ - GL_TEXTURE0; }
  [[nodiscard]] rgba_t* GetPixelData() const { return pixel_data_; }

  void SetForceChannels(int force_channels) { m_force_channels_ = force_channels; }

 protected:
  static GLuint VACCANT_TEX_TARGET;

  int m_force_channels_;
  rgba_t* pixel_data_;
  int h, w;
  GLuint target_;
  GLuint id_;
};

typedef std::shared_ptr<Texture> Texture_p;

template<typename... _Args>
Texture_p CreateTexture(_Args&&... __args) {
  return std::make_shared<Texture>(std::forward<_Args>(__args)...);
}

}  // namespace fae
