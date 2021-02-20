#include "AnimatedGameObject.hpp"

#include "../Event.hpp"

namespace fae {

bool AnimatedGameObject::HandleEvent(const FrameEvent& e) {
  if (!(e.GetFramesDrawn() % (e.GetFps() / texture_->GetFps()))) {
    AnimatedTexture* tex = dynamic_cast<AnimatedTexture*>(texture_.get());
    texture_segment_t seg = tex->GetNextSegment(segment_to_draw_++);
    SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
    segment_to_draw_ = segment_to_draw_ % tex->GetSegmentCount();
  }
  return true;
}

}  // namespace fae
