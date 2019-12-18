#pragma once

#include "DynamicGameObject.hpp"
#include "IControlable.hpp"
#include "IListenable.hpp"

namespace fae {

class ControllableGameObject: public DynamicGameObject, public IKeyControlable, public IListenable {
private:
    int m_last_key_pressed;
    int segment_to_draw;
    bool animation_started;
    point3_t per_frame_move;
    float m_speed;
    int frames_before_idle;
    std::shared_ptr<AnimatedTexture> p_texture_left;
    std::shared_ptr<AnimatedTexture> p_texture_right;
    std::shared_ptr<AnimatedTexture> p_texture_up;
    std::shared_ptr<AnimatedTexture> p_texture_down;
    std::shared_ptr<AnimatedTexture> p_texture_idle;
    std::shared_ptr<AnimatedTexture> next_frame_anim;
    //p_texture is current animation playing

    void PlayAnimation(std::shared_ptr<AnimatedTexture> anim) {
        if (animation_started && (p_texture == anim))
            return;
        next_frame_anim = anim;
        animation_started = true;
    }

public:
    ControllableGameObject() {
        std::cout << "[->]\tControllableGameObject" << std::endl;
        segment_to_draw = 0;
        m_speed = 10.0f;
        frames_before_idle = 10;
    }

    virtual ~ControllableGameObject() { }

    inline void SetLeftAnimation(AnimatedTexture_p left) { p_texture_left = left; }
    inline void SetRightAnimation(AnimatedTexture_p right) { p_texture_right = right; }
    inline void SetUpAnimation(AnimatedTexture_p up) { p_texture_up = up; }
    inline void SetDownAnimation(AnimatedTexture_p down) { p_texture_down = down; }
    inline void SetIdleAnimation(AnimatedTexture_p idle) { p_texture_idle = idle; SetTexture(idle);}

    void OnEvent(Event& e) final;

    bool OnFrame(FrameEvent& e) final;

    bool OnKeyPressed(KeyPressedEvent& e) final;

    void AddEventListener(std::shared_ptr<IEventListener> object) final;

    inline void SetSpeed(float speed) { m_speed = speed; }
};

typedef std::shared_ptr<ControllableGameObject> ControllableGameObject_p;

template<typename... _Args>
ControllableGameObject_p CreateControllableGameObject(_Args&&... __args) {
    return std::make_shared<ControllableGameObject>(std::forward<_Args>(__args)...);
}

}