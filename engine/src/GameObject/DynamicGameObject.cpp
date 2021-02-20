#include "DynamicGameObject.hpp"

#include "FAEUtils.h"

#include "glm/ext.hpp"

namespace fae {

void DynamicGameObject::SetTexture(std::shared_ptr<AnimatedTexture> texture) {
  if (!texture) {
    std::cout << "DynamicGameObject::SetTexture::Error: texture is not set" << std::endl;
    return;
  }

  texture_ = texture;
  texture_segment_t seg = texture->GetSegment(0, 0);
  SetTextureCoords(seg.rt, seg.rb, seg.lb, seg.lt);
  GameObject::SetCoords({-texture->GetSegmentW()/2.f, -texture->GetSegmentH()/2.f},
      {texture->GetSegmentW()/2.f, texture->GetSegmentH()/2.f});
}

void DynamicGameObject::UseShaderProgram() {
  GLCall(glUseProgram(shader_program_));
  GLint model_mtx_loc = GLCall(glGetUniformLocation(shader_program_, "model"));
  GLint texture_loc = GLCall(glGetUniformLocation(shader_program_, "Texture"));
  GLCall(glUniformMatrix4fv(model_mtx_loc, 1, GL_FALSE, glm::value_ptr(model_mtx_.GetModelMtx())));
  GLCall(glUniform1i(texture_loc, texture_->GetTargetN()));
}

void DynamicGameObject::SetCoords(point3_t lb) {
  if (!texture_) {
    std::cout << "GameObject::SetCoords::Error: texture is not set" << std::endl;
    return;
  }

  vertexes_[0].coords = {lb.x + texture_->GetH(), lb.y + texture_->GetW(),   lb.z};
  vertexes_[1].coords = {lb.x + texture_->GetH(), lb.y,                       lb.z};
  vertexes_[2].coords = {lb.x,                     lb.y,                       lb.z};
  vertexes_[3].coords = {lb.x,                     lb.y + texture_->GetW(),   lb.z};

  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }
  vertex_buffer_->ReloadData(vertexes_);
}

}  // namespace fae
