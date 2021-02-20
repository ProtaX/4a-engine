#pragma once

#include <string>
#include <utility>
#include <memory>

#include "GL/glew.h"
#include "SOIL.h"

namespace fae {

constexpr int RGBA_TEXTURE = SOIL_LOAD_RGBA;
using rgba_t = uint8_t;

class Texture {
 public:
  explicit Texture(int force_channels = RGBA_TEXTURE) noexcept;

  explicit Texture(const std::string& path, int force_channels = RGBA_TEXTURE);

  virtual ~Texture();

  bool Load(const std::string& path);

  [[nodiscard]] int GetH() const;
  [[nodiscard]] int GetW() const;
  [[nodiscard]] GLuint GetTargetN() const;
  [[nodiscard]] rgba_t* GetPixelData() const;

  void SetForceChannels(int force_channels);

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
