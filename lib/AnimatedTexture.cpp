#include "AnimatedTexture.hpp"

namespace fae {

void AnimatedTexture::SetGrid(unsigned int columns, unsigned int rows) {
    if (!pixel_data) {
        std::cout << "AnimatedTexture::SetGrid::Error: pixel data is not set" << std::endl;
        return;
    }
    m_columns = columns;
    m_rows = rows;

    for (float i = 0; i < columns; i++) {
        for (float j = 0; j < rows; j++) {
            texture_segment_t seg ={{i/columns, j/rows},
                                    {i/columns, (j+1.f)/rows},
                                    {(i+1.f)/columns, (j+1.f)/rows},
                                    {(i+1.f)/columns, j/rows}};
            grid.push_back(seg);
        }
    }
}

texture_segment_t AnimatedTexture::GetSegment(int x, int y) const {
    if (grid.size() < y * m_rows + x) {
        std::cout << "AnimatedTexture::GetSegment::Error: no such segment" << std::endl;
        return {};
    }
    return grid[y * m_rows + x];
}

}