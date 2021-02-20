#pragma once

#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "Texture.hpp"
#include "Core.hpp"

namespace fae {

class AnimatedTexture: public Texture {
 public:
  explicit AnimatedTexture(int force_channels = RGBA_TEXTURE) noexcept:
    Texture(force_channels),
    columns_(0),
    rows_(0),
    fps_(0)
    { }
  explicit AnimatedTexture(const std::string& path, int force_channels = RGBA_TEXTURE) noexcept:
    Texture(path, force_channels),
    columns_(1),
    rows_(1),
    fps_(1) {
      SetGrid(1, 1);
    }
  virtual ~AnimatedTexture() {}

  void SetGrid(uint32_t columns, uint32_t rows);
  void SetFps(uint32_t fps) { fps_ = fps; }

  [[nodiscard]] texture_segment_t GetSegment(int x, int y) const;
  [[nodiscard]] texture_segment_t GetNextSegment(int i) const { return grid[i]; }
  [[nodiscard]] uint32_t GetSegmentW() const { return (w/static_cast<float>(columns_)); }
  [[nodiscard]] uint32_t GetSegmentH() const { return (h/static_cast<float>(rows_)); }
  [[nodiscard]] uint32_t GetSegmentCount() const { return (rows_ * columns_); }
  [[nodiscard]] uint32_t GetFps() const { return fps_; }

 private:
  uint32_t columns_, rows_;
  uint32_t fps_;
  std::vector<texture_segment_t> grid;
};

typedef std::shared_ptr<AnimatedTexture> AnimatedTexture_p;

template<typename... _Args>
AnimatedTexture_p CreateAnimatedTexture(_Args&&... __args) {
  return std::make_shared<AnimatedTexture>(std::forward<_Args>(__args)...);
}

}  // namespace fae
