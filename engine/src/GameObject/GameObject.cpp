#include "GameObject.hpp"

#include "glm/ext.hpp"

namespace fae {

void GameObject::SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  vertexes_[0].tex_coords = rt;
  vertexes_[1].tex_coords = rb;
  vertexes_[2].tex_coords = lb;
  vertexes_[3].tex_coords = lt;
  vertex_buffer_->ReloadData(vertexes_);
}

void GameObject::SetCoords(point3_t lb, point3_t lt, point3_t rt, point3_t rb) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  vertexes_[0].coords = rt;
  vertexes_[1].coords = rb;
  vertexes_[2].coords = lb;
  vertexes_[3].coords = lt;
  vertex_buffer_->ReloadData(vertexes_);
}

void GameObject::SetCoords(point3_t lb, point3_t rt) {
  if (lb.z != rt.z) {
    std::cout << "GameObject::SetCoords::Error: Bad z coordinate" << std::endl;
    return;
  }
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  vertexes_[0].coords = {rt.x, rt.y, lb.z};
  vertexes_[1].coords = {rt.x, lb.y, lb.z};
  vertexes_[2].coords = {lb.x, lb.y, lb.z};
  vertexes_[3].coords = {lb.x, rt.y, lb.z};
  vertex_buffer_->ReloadData(vertexes_);
}

void GameObject::SetSize(point2_t rt) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  vertexes_[0].coords = {rt.x, rt.y, 0.};
  vertexes_[1].coords = {rt.x, 0.,   0.};
  vertexes_[2].coords = {0.,   0.,   0.};
  vertexes_[3].coords = {0.,   rt.y, 0.};
  vertex_buffer_->ReloadData(vertexes_);
}

void GameObject::SetLayer(float z) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  vertexes_[0].coords.z = z;
  vertexes_[1].coords.z = z;
  vertexes_[2].coords.z = z;
  vertexes_[3].coords.z = z;
  vertex_buffer_->ReloadData(vertexes_);
}

GameObject::GameObject() noexcept {
  id_ = (game_object_id)this;
  vertex_buffer_ = std::make_unique<VertexBuffer>(vertexes_, sizeof(vertexes_));
  vertex_layout_ = std::make_unique<VertexLayout>();
  index_buffer_ = std::make_unique<IndexBuffer>(indexes_, sizeof(indexes_));
  vertex_array_ = std::make_unique<VertexArray>();

  SetTextureCoords({1., 1.},
                   {1., 0.},
                   {0., 0.},
                   {0., 1.});

  vertex_layout_->Push<float>(3);
  vertex_layout_->Push<float>(3);
  vertex_layout_->Push<float>(2);

  vertex_array_->Bind();
  index_buffer_->Bind();
  vertex_array_->AddBuffer(vertex_buffer_, vertex_layout_);
  vertex_array_->Unbind();

  std::cout << "[Created] GameObject " << id_ << std::endl;
}

float GameObject::GetLayer() {
  if ((vertexes_[0].coords.z == vertexes_[1].coords.z) &&
      (vertexes_[2].coords.z == vertexes_[3].coords.z) &&
      (vertexes_[1].coords.z == vertexes_[2].coords.z))
    return vertexes_[0].coords.z;
  else
    return -1.0f;
}

GameObject::GameObject(GameObject&& right) {
  id_ = right.id_;
  vertex_buffer_ = std::move(right.vertex_buffer_);
  vertex_array_ = std::move(right.vertex_array_);
  vertex_layout_ = std::move(right.vertex_layout_);
  index_buffer_ = std::move(right.index_buffer_);

  model_mtx_ = right.model_mtx_;
  vertexes_[0] = right.vertexes_[0];
  vertexes_[1] = right.vertexes_[1];
  vertexes_[2] = right.vertexes_[2];
  vertexes_[3] = right.vertexes_[3];
  shader_program_ = right.shader_program_;
  std::cout << "[Moved] GameObject " << id_ << std::endl;
}

GameObject::GameObject(const GameObject& right) {
  id_ = right.id_;
  vertex_buffer_ = std::make_unique<VertexBuffer>(vertexes_, sizeof(vertexes_));
  vertex_layout_ = std::make_unique<VertexLayout>();
  index_buffer_ = std::make_unique<IndexBuffer>(indexes_, sizeof(indexes_));
  vertex_array_ = std::make_unique<VertexArray>();

  SetTextureCoords({1., 1.},
                   {1., 0.},
                   {0., 0.},
                   {0., 1.});

  vertex_layout_->Push<float>(3);
  vertex_layout_->Push<float>(3);
  vertex_layout_->Push<float>(2);

  vertex_array_->Bind();
  index_buffer_->Bind();
  vertex_array_->AddBuffer(vertex_buffer_, vertex_layout_);
  vertex_array_->Unbind();

  model_mtx_ = right.model_mtx_;
  vertexes_[0] = right.vertexes_[0];
  vertexes_[1] = right.vertexes_[1];
  vertexes_[2] = right.vertexes_[2];
  vertexes_[3] = right.vertexes_[3];
  shader_program_ = right.shader_program_;
  std::cout << "[Copied] GameObject " << id_ << std::endl;
}

GameObject& GameObject::operator=(const GameObject& right) {
  id_ = right.id_;
  model_mtx_ = right.model_mtx_;
  vertexes_[0] = right.vertexes_[0];
  vertexes_[1] = right.vertexes_[1];
  vertexes_[2] = right.vertexes_[2];
  vertexes_[3] = right.vertexes_[3];
  shader_program_ = right.shader_program_;

  return *this;
}

bool GameObject::operator<(const GameObject& right) {
  if ((this->vertexes_[0].coords.z < right.vertexes_[0].coords.z) &&
      (this->vertexes_[1].coords.z < right.vertexes_[1].coords.z) &&
      (this->vertexes_[2].coords.z < right.vertexes_[2].coords.z) &&
      (this->vertexes_[3].coords.z < right.vertexes_[3].coords.z))
    return true;
  return false;
}

void GameObject::Scale(float percent) {
  model_mtx_.scale = glm::scale(model_mtx_.scale, glm::vec3(percent, percent, percent));
}

void GameObject::Scale(point3_t percent) {
  model_mtx_.scale = glm::scale(model_mtx_.scale, glm::vec3(percent.x, percent.y, percent.z));
}

void GameObject::Move(point3_t value) {
  model_mtx_.translation = glm::translate(model_mtx_.translation, glm::vec3(value.x, value.y, value.z));
}

void GameObject::MoveTo(point3_t value) {
  //m_model_mtx.translation = glm::translate(m_model_mtx.translation, glm::vec3(value.x, value.y, value.z));
}

GameObject::~GameObject() {
    if (!index_buffer_ &&
      !vertex_array_ &&
      !vertex_buffer_ &&
      !vertex_layout_) {
        std::cout << "[~] Empty GameObject " << id_ << std::endl;
      } else {
        std::cout << "[~] GameObject " << id_ << std::endl;
      }
  }

}  // namespace fae
