#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>

#include "Core.hpp"

namespace fae {

/**
 * Handle all these event types in IEventListener::OnEvent
 * to avoid compiler warnings
 **/
enum class EventType {
  None,
  KeyPressed,
  KeyReleased,
  Frame,
  PlayerMove
};

class Event {
 public:
  [[nodiscard]] virtual const EventType GetEventType() const = 0;
  [[nodiscard]] virtual const std::string ToString() const { return std::string("Event"); }
  [[nodiscard]] bool IsHandled() const { return hanled_; }
  bool& Handle() { return hanled_; }
  virtual ~Event() { }

 protected:
  bool hanled_;
  Event() noexcept: hanled_(false) { }
};

class KeyEvent: public Event {
 public:
  [[nodiscard]] virtual const EventType GetEventType() const = 0;
  [[nodiscard]] const std::string ToString() const override { return std::string("KeyEvent"); }

 protected:
  int keycode_;
  explicit KeyEvent(int keycode) noexcept: keycode_(keycode) { }
};

class KeyPressedEvent: public KeyEvent {
 public:
  explicit KeyPressedEvent(int keycode, int repeat_count = 0) noexcept:
    KeyEvent(keycode), repeat_count_(repeat_count) { }

  [[nodiscard]] const EventType GetEventType() const final { return EventType::KeyPressed; }
  [[nodiscard]] const int GetKeyCode() const { return this->keycode_; }
  [[nodiscard]] const int GetRepeatCount() const { return this->repeat_count_; }
  [[nodiscard]] const std::string ToString() const final { return std::string("KeyPressed"); }

 private:
  int repeat_count_;
};

class FrameEvent: public Event {
 public:
  FrameEvent(uint32_t frames_drawn, uint32_t fps) noexcept:
             frames_drawn_(frames_drawn),
             fps_(fps) { }

  [[nodiscard]] const EventType GetEventType() const final { return EventType::Frame; }
  [[nodiscard]] const uint32_t GetFramesDrawn() const { return this->frames_drawn_; }
  [[nodiscard]] const uint32_t GetFps() const { return this->fps_; }
  [[nodiscard]] const std::string ToString() const final { return std::string("Frame"); }

 private:
  uint32_t frames_drawn_;
  uint32_t fps_;
};

class PlayerMoveEvent: public Event {
 public:
  PlayerMoveEvent(point3_t move, uint32_t frames_for_move) noexcept:
    move_vec_(move),
    frames_for_move_(frames_for_move) { }
  [[nodiscard]] const EventType GetEventType() const final { return EventType::PlayerMove; }
  [[nodiscard]] const point3_t GetMove() const { return this->move_vec_; }
  [[nodiscard]] const uint32_t GetFrames() const { return this->frames_for_move_; }
  [[nodiscard]] const std::string ToString() const final { return std::string("PlayerMove"); }

 private:
  point3_t move_vec_;
  uint32_t frames_for_move_;
};

class IEventListener {
 public:
  bool OnEvent(const Event& e) {
    switch (e.GetEventType()) {
    case EventType::Frame:
      return HandleEvent(static_cast<const FrameEvent&>(e));
    case EventType::KeyPressed:
      return HandleEvent(static_cast<const KeyPressedEvent&>(e));
    case EventType::PlayerMove:
      return HandleEvent(static_cast<const PlayerMoveEvent&>(e));
    case EventType::KeyReleased:
    case EventType::None:
      break;
    }
    return false;
  }

 protected:
  virtual bool HandleEvent(const FrameEvent&)      { return false; }
  virtual bool HandleEvent(const KeyPressedEvent&) { return false; }
  virtual bool HandleEvent(const PlayerMoveEvent&) { return false; }
};

typedef std::function<void(const Event&)> EventCB;

class IListenable {
 public:
  virtual void AddEventListener(EventType t, std::shared_ptr<IEventListener> object) = 0;

  [[nodiscard]] std::vector<EventCB>& GetCallbacks(EventType t);

 protected:
  void AddCallback(EventType t, EventCB cb);

 private:
  std::map<EventType, std::vector<EventCB>> type_handlers_;
};

}  // namespace fae
