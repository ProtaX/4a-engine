#pragma once

#include "Event.hpp"
#include "Texture.hpp"
#include "IControlable.hpp"

namespace fae {

class ImageProxy: public Texture, public IEventListener {
private:
    /* Actual texture */
    Texture_p real_obj;

    /* Caching for lazy init */
    std::string m_cache_path;

    /* Идея: этот класс реализует интерфейс слушателя кликов
     * по событию клика создается реальная текстура из кэшированных данных
     * до ее создания все вызовы либо кэшируются, либо возвращается черный пиксель
     * после клика все вызовы проксируются новой текстуре
    */

   void OnSpacePressed(KeyPressedEvent& e);

public:
    ImageProxy(const std::string& path, int force_channels = RGBA_TEXTURE):
        Texture(force_channels) { 
        m_cache_path = std::string(path);
        pixel_data = new uint8_t[4];
        uint8_t black[4] = {0,0,0,255};
        std::memcpy(pixel_data, black, 4);

        h = 1;
        w = 1;

        target = Texture::vaccant_tex_target;
        float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
        GLCall(glGenTextures(1, &id));
        GLCall(glActiveTexture(Texture::vaccant_tex_target++));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data));
        GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }

    ImageProxy(int force_channels = RGBA_TEXTURE): 
        Texture(force_channels) {
        pixel_data = new uint8_t[4];
        uint8_t black[4] = {0,0,0,255};
        std::memcpy(pixel_data, black, 4);

        h = 1;
        w = 1;

        target = Texture::vaccant_tex_target;
        float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
        GLCall(glGenTextures(1, &id));
        GLCall(glActiveTexture(Texture::vaccant_tex_target++));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data));
        GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }

    virtual bool LoadImage(const std::string& path);

    virtual inline int GetH() const;

    virtual inline int GetW() const;

    virtual inline GLuint GetTargetN() const;

    virtual inline void ForceChannels(int force_channels);
    
    virtual inline rgba_t* GetPixelData() const;

    void OnEvent(Event& e) final;

    virtual ~ImageProxy();
};

typedef std::shared_ptr<ImageProxy> ImageProxy_p;

template<typename... _Args>
ImageProxy_p CreateImageProxy(_Args&&... __args) {
    return std::make_shared<ImageProxy>(std::forward<_Args>(__args)...);
}

}