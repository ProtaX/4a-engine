#pragma once

#include "Core.hpp"

namespace fae {

enum class EventType {
    None = 0,
    KeyPressed, KeyReleased,
    Frame,
    PlayerMove
};

class Event {
public:
    virtual inline EventType GetEventType() const = 0;
    virtual inline std::string ToString() const { return "Event"; }
    inline int IsHandled() const { return m_hanled; }
    virtual ~Event() { }
    int m_hanled;
protected:
    Event(): m_hanled(0) { }
};

class KeyEvent: public Event {
public:
    virtual inline EventType GetEventType() const = 0;
    virtual inline std::string ToString() const override { return "KeyEvent"; }

protected:
    int m_keycode;
    KeyEvent(int keycode): m_keycode(keycode) { }
};

class KeyPressedEvent: public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeat_count = 0): 
        KeyEvent(keycode), m_repeat_count(repeat_count) { }
    
    virtual inline EventType GetEventType() const override { return EventType::KeyPressed; }
    virtual inline std::string ToString() const override { return "KeyPressed"; }
    inline int GetKeyCode() const { return this->m_keycode; }
    inline int GetRepeatCount() const { return this->m_repeat_count; }
private:
    int m_repeat_count;
};

class FrameEvent: public Event {
private:
    int m_frames_drawn;
    int m_fps;
public:
    FrameEvent(int frames_drawn, int fps):
        m_frames_drawn(frames_drawn),
        m_fps(fps) { }
    
    virtual inline EventType GetEventType() const override { return EventType::Frame; }
    virtual inline std::string ToString() const override { return "Frame"; }
    inline int GetFramesDrawn() const { return this->m_frames_drawn; }
    inline int GetFps() const { return this->m_fps; }
};

class PlayerMoveEvent: public Event {
private:
    point3_t m_move_vec;
    int m_frames_for_move;
public:
    PlayerMoveEvent(point3_t move, int frames_for_move):
        m_move_vec(move),
        m_frames_for_move(frames_for_move) { }
    virtual inline EventType GetEventType() const override { return EventType::PlayerMove; }
    virtual inline std::string ToString() const override { return "PlayerMove"; }
    inline point3_t GetMove() const { return this->m_move_vec; }
    inline int GetFrames() const { return this->m_frames_for_move; }
};

class EventDispatcher {
private:
    Event& m_event;

public:
    EventDispatcher(Event& event): m_event(event) { }

    template<typename T, typename F>
    void Dispatch(const F& func) {
        if (!dynamic_cast<T*>(&m_event))
            return;
        func(static_cast<T&>(m_event));
    }
};

}