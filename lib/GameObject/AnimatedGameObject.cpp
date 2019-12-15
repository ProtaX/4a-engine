#include "AnimatedGameObject.hpp"

namespace fae {

bool AnimatedGameObject::OnFrame(FrameEvent& e) {
    if (! (e.GetFramesDrawn() % frames_until_next_segment)) {
        AnimatedTexture* tex = dynamic_cast<AnimatedTexture*>(p_texture.get());
        texture_segment_t seg = tex->GetNextSegment(segment_to_draw++);
        SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
        segment_to_draw = segment_to_draw % tex->GetSegmentCount();
    }
    return true;
}

void AnimatedGameObject::OnEvent(Event& e) {
    EventDispatcher disp(e);

    disp.Dispatch<FrameEvent>(std::bind(&OnFrame, this, std::placeholders::_1));
}



}