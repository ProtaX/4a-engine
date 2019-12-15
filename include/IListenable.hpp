#pragma once

#include <list>
#include <functional>
#include "Event.hpp"
#include "GameObject.hpp"

namespace fae {

class IListenable {
protected:
    std::list<std::function<void(Event&)>> m_callbacks;
public:
    virtual void AddEventListener(std::shared_ptr<IEventListener> object) = 0;
};

}