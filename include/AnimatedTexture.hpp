#pragma once

#include "Core.hpp"
#include "Texture.hpp"
#include <vector>

namespace fae {

class AnimatedTexture: public Texture {
private:
    unsigned int m_columns, m_rows;
    int m_fps;
    std::vector<texture_segment_t> grid;
public:
    AnimatedTexture(int force_channels = RGBA_TEXTURE): 
        Texture(force_channels),
        m_columns(0),
        m_rows(0),
        m_fps(0)
        { }
    AnimatedTexture(const std::string& path, int force_channels = RGBA_TEXTURE):
        Texture(path, force_channels),
        m_columns(1),
        m_rows(1),
        m_fps(1)
        { 
            SetGrid(1, 1);
        }
    virtual ~AnimatedTexture() {}

    void SetGrid(unsigned int columns, unsigned int rows);
    void SetFps(int fps) { m_fps = fps; }

    texture_segment_t GetSegment(int x, int y) const;
    inline texture_segment_t GetNextSegment(int i) const { return grid[i]; }
    inline int GetSegmentW() const { return (w/(float)m_columns); }
    inline int GetSegmentH() const { return (h/(float)m_rows); }
    inline int GetSegmentCount() const { return (m_rows * m_columns); }
    inline int GetFps() const { return m_fps; }
};

typedef std::shared_ptr<AnimatedTexture> AnimatedTexture_p;

template<typename... _Args>
AnimatedTexture_p CreateAnimatedTexture(_Args&&... __args) {
    return std::make_shared<AnimatedTexture>(std::forward<_Args>(__args)...);
}

}