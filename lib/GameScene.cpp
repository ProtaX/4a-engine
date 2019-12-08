#include <GameScene.hpp>
#include <algorithm>

namespace fae {

GameScene::GameScene() {
}

game_object_id GameScene::UploadObject(std::shared_ptr<GameObject> obj) {
    game_object_id added_id = m_scene_storage.insert(std::pair<float, std::shared_ptr<GameObject>>(obj->GetLayer(), std::move(obj)))->second->GetId();
    return added_id;
}

void GameScene::Draw() {
    for (auto& pair: m_scene_storage) {
        GameObject* object = pair.second.get();
        object->ChangeState();
        object->UseShaderProgram();
        glm::mat4 proj = p_camera->GetProj();
        glm::mat4 view = p_camera->GetVeiw();
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

//TODO: сделать оптимизированный поиск
GameObject* GameScene::GetObjectById(game_object_id id) {
    for (auto& pair: m_scene_storage)
        if (pair.second->GetId() == id)
            return pair.second.get();
    return nullptr;
}

}