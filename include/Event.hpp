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
protected:
    int m_hanled;
    Event(): m_hanled(0) { }
};

class KeyEvent: protected Event {
public:
    virtual inline EventType GetEventType() const = 0;
    virtual inline std::string ToString() const override { return "KeyEvent"; }

protected:
    int m_keycode;
    KeyEvent(int keycode): m_keycode(keycode) { }
};

class KeyPressedEvent: public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeat_count): 
        KeyEvent(keycode), m_repeat_count(repeat_count) { }
    
    virtual inline EventType GetEventType() const override { return EventType::KeyPressed; }
    virtual inline std::string ToString() const override { return "KeyPressed"; }
private:
    int m_repeat_count;
};

}