#include <GameScene.hpp>

namespace fae {

void GameScene::AddObject(GameObject& obj) {
    //TODO: добавить сортировку по признаку
    //координаты z
    m_scene_storage.push_back(std::move(obj));
}

void GameScene::Draw() {
    for (auto& object: m_scene_storage) {
        object.UseShaderProgram();
        glm::mat4 proj = p_camera->GetProj();
        glm::mat4 view = p_camera->GetVeiw();
        int current_shader = object.GetShaderProgram();
        GLint proj_location = GLCall(glGetUniformLocation(current_shader, "proj"));
        GLint view_location = GLCall(glGetUniformLocation(current_shader, "view"));
        GLCall(glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj)));
        GLCall(glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view)));
        object.BindVertexArray();
        object.BindVertexBuffer();
        object.BindIndexBuffer();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        object.UnbindVertexBuffer();
        object.UnbindIndexBuffer();
        object.UnbindVertexArray();
    }
}

}