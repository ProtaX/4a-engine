#include "AnimatedTexture.hpp"

namespace fae {

void AnimatedTexture::SetGrid(unsigned int columns, unsigned int rows) {
  if (!pixel_data_) {
    std::cout << "AnimatedTexture::SetGrid::Error: pixel data is not set" << std::endl;
    return;
  }

  columns_ = columns;
  rows_ = rows;
  fps_ = rows * columns;
  if (!grid.empty())
    grid.clear();

  for (float i = 0; i < columns; ++i) {
    for (float j = 0; j < rows; ++j) {
      texture_segment_t seg ={{i/columns,       j/rows},
                              {i/columns,       (j+1.f)/rows},
                              {(i+1.f)/columns, (j+1.f)/rows},
                              {(i+1.f)/columns, j/rows}};
      grid.push_back(seg);
    }
  }
}

texture_segment_t AnimatedTexture::GetSegment(int x, int y) const {
  if (grid.size() < y * rows_ + x) {
    std::cout << "AnimatedTexture::GetSegment::Error: no such segment" << std::endl;
    return {};
  }
  return grid[y * rows_ + x];
}

}  // namespace fae
