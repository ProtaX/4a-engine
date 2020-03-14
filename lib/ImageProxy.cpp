#include "Core.hpp"
#include "ImageProxy.hpp"
#include <functional>

namespace fae {

bool ImageProxy::LoadImage(const std::string& path) {
    if (real_obj)
        return real_obj->LoadImage(path);
    else {
        m_cache_path.clear();
        m_cache_path = path;
    }
    return true;
}

inline int ImageProxy::GetH() const { 
    if (real_obj)
        return real_obj->GetH();
    return 1;
}

inline int ImageProxy::GetW() const {
    if (real_obj)
        return real_obj->GetW();
    return 1;
}

inline GLuint ImageProxy::GetTargetN() const { 
    if (real_obj)
        return real_obj->GetTargetN();
    return target - GL_TEXTURE0;
}

inline void ImageProxy::ForceChannels(int force_channels) { 
    if (real_obj)
        real_obj->ForceChannels(force_channels);
}

inline rgba_t* ImageProxy::GetPixelData() const { 
    if (real_obj)
        return real_obj->GetPixelData();
    return pixel_data;
}

ImageProxy::~ImageProxy() {
    if (real_obj)
        real_obj->~Texture();
    else 
        delete[] pixel_data;
}

void ImageProxy::OnEvent(Event& e) {
    EventDispatcher disp(e);

    disp.Dispatch<KeyPressedEvent>(std::bind(&OnSpacePressed, this, std::placeholders::_1));
}

void ImageProxy::OnSpacePressed(KeyPressedEvent& e) {
    delete[] pixel_data;
    if (!real_obj)
        real_obj = CreateTexture(m_cache_path, m_force_channels);
}

}