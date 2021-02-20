#include "GameScene.hpp"

#include <algorithm>

namespace fae {

void GameScene::AddObject(std::shared_ptr<GameObject> obj) {
  scene_storage_.insert({obj->GetLayer(), obj});
}

void GameScene::Draw() const {
  for (const auto& pair : scene_storage_) {
    GameObject* object = pair.second.get();
    object->UseShaderProgram();
    glm::mat4 proj = camera_->GetProj();
    glm::mat4 view = camera_->GetVeiw();
    int current_shader = object->GetShaderProgram();
    GLint proj_location = GLCall(glGetUniformLocation(current_shader, "proj"));
    GLint view_location = GLCall(glGetUniformLocation(current_shader, "view"));
    GLCall(glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj)));
    GLCall(glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view)));
    object->BindVertexArray();
    object->BindVertexBuffer();
    object->BindIndexBuffer();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    object->UnbindVertexBuffer();
    object->UnbindIndexBuffer();
    object->UnbindVertexArray();
  }
}

}  // namespace fae
