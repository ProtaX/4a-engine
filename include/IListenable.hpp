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

class IFrameListenable {
protected:
    std::list<std::function<void(Event&)>> m_frame_callbacks;
public:
    virtual void AddFrameListener(std::shared_ptr<IEventListener> object) = 0;
};

class IKeyListenable {
protected:
    std::list<std::function<void(Event&)>> m_key_callbacks;
public:
    virtual void AddKeyListener(std::shared_ptr<IEventListener> object) = 0;
};

class IMoveListenable {
protected:
    std::list<std::function<void(Event&)>> m_move_callbacks;
public:
    virtual void AddMoveListener(std::shared_ptr<IEventListener> object) = 0;
};

class ICollidable {
protected:
    std::list<std::function<void(Event&)>> m_collision_callbacks;
public:
    virtual void AddCollisionListener(std::shared_ptr<IEventListener> object) = 0;
};

}