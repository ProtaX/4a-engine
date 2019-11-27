#pragma once

#include "Core.hpp"

namespace fae {

enum class EventType {
    None = 0,
    KeyPressed, KeyReleased
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

//Обертка вокруг класса события
class EventDispatcher {
private:
    Event& m_event;

public:
    EventDispatcher(Event& event): m_event(event) { }

    template<typename T, typename F>
    void Dispatch(const F& func) {
        m_event.m_hanled = func(static_cast<T&>(m_event));
    }
};

}