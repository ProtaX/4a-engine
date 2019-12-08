#pragma once

#include "Event.hpp"

namespace fae {

class IControlable {
public:
    virtual void OnEvent(Event& e) = 0;
    virtual ~IControlable() { }
protected:
    IControlable() { }
};

class IKeyControlable: public IControlable {
public:
    virtual bool OnKeyPressed(KeyPressedEvent& e) = 0;
    virtual ~IKeyControlable() { }
protected:
    IKeyControlable() { }
};

}