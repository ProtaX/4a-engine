#pragma once

#include "Event.hpp"

namespace fae {

class IEventListener {
public:
    virtual void OnEvent(Event& e) = 0;
    virtual ~IEventListener() { }
protected:
    IEventListener() { }
};

class IKeyControlable {
public:
    virtual bool OnKeyPressed(KeyPressedEvent& e) = 0;
    virtual ~IKeyControlable() { }
protected:
    IKeyControlable() { }
};

}