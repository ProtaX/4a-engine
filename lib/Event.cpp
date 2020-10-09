#include "Event.hpp"

namespace fae {

std::vector<EventCB>& IListenable::GetCallbacks(EventType t) {
  return type_handlers_.at(t);
}

void IListenable::AddCallback(EventType t, EventCB cb) {
  type_handlers_[t].push_back(cb);
}

}  // namespace fae
