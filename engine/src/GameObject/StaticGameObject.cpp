#include "StaticGameObject.hpp"

#include "FAEUtils.h"

#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

namespace fae {

bool StaticGameObject::HandleEvent(const KeyPressedEvent& e) {
  int keycode = e.GetKeyCode();

  if (keycode == GLFW_KEY_W)
    Move({0., 5.});
  else if (keycode == GLFW_KEY_A)
    Move({-5.});
  else if (keycode == GLFW_KEY_S)
    Move({0., -5.});
  else if (keycode == GLFW_KEY_D)
    Move({5.});
  else
    return false;

  return true;
}

void StaticGameObject::SetTexture(std::shared_ptr<Texture> texture) {
  p_texture = texture;
  GameObject::SetCoords({-texture->GetW()/2.f, -texture->GetH()/2.f}, {texture->GetW()/2.f, texture->GetH()/2.f});
}

void StaticGameObject::SetCoords(point3_t lb) {
  if (!p_texture) {
    std::cout << "GameObject::SetCoords::Error: texture is not set" << std::endl;
    return;
  }
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  vertexes_[0].coords = {lb.x + p_texture->GetH(), lb.y + p_texture->GetW(),   lb.z};
  vertexes_[1].coords = {lb.x + p_texture->GetH(), lb.y,                       lb.z};
  vertexes_[2].coords = {lb.x,                     lb.y,                       lb.z};
  vertexes_[3].coords = {lb.x,                     lb.y + p_texture->GetW(),   lb.z};
  vertex_buffer_->ReloadData(vertexes_);
}

// TODO: move gl shader code into glshader class
void StaticGameObject::UseShaderProgram() {
  GLCall(glUseProgram(shader_program_));
  GLint model_mtx_loc = GLCall(glGetUniformLocation(shader_program_, "model"));
  GLint texture_loc = GLCall(glGetUniformLocation(shader_program_, "Texture"));
  GLCall(glUniformMatrix4fv(model_mtx_loc, 1, GL_FALSE, glm::value_ptr(model_mtx_.GetModelMtx())));
  GLCall(glUniform1i(texture_loc, p_texture->GetTargetN()));
}

}  // namespace fae
