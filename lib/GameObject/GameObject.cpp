#include "GameObject.hpp"

namespace fae {

void GameObject::SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  verticies_[0].tex_coords = rt;
  verticies_[1].tex_coords = rb;
  verticies_[2].tex_coords = lb;
  verticies_[3].tex_coords = lt;
  vertex_buffer_->ReloadData(verticies_);
}

void GameObject::SetCoords(point3_t lb, point3_t lt, point3_t rt, point3_t rb) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  verticies_[0].coords = rt;
  verticies_[1].coords = rb;
  verticies_[2].coords = lb;
  verticies_[3].coords = lt;
  vertex_buffer_->ReloadData(verticies_);
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

  verticies_[0].coords = {rt.x, rt.y, lb.z};
  verticies_[1].coords = {rt.x, lb.y, lb.z};
  verticies_[2].coords = {lb.x, lb.y, lb.z};
  verticies_[3].coords = {lb.x, rt.y, lb.z};
  vertex_buffer_->ReloadData(verticies_);
}

void GameObject::SetSize(point2_t rt) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  verticies_[0].coords = {rt.x, rt.y, 0.};
  verticies_[1].coords = {rt.x, 0.,   0.};
  verticies_[2].coords = {0.,   0.,   0.};
  verticies_[3].coords = {0.,   rt.y, 0.};
  vertex_buffer_->ReloadData(verticies_);
}

void GameObject::SetLayer(float z) {
  if (!vertex_buffer_) {
    std::cout << "GameObject::SetCoords::Error: VBO is not set" << std::endl;
    return;
  }

  verticies_[0].coords.z = z;
  verticies_[1].coords.z = z;
  verticies_[2].coords.z = z;
  verticies_[3].coords.z = z;
  vertex_buffer_->ReloadData(verticies_);
}

GameObject::GameObject() noexcept {
  id_ = (game_object_id)this;
  vertex_buffer_ = std::make_unique<VertexBuffer>(verticies_, sizeof(verticies_));
  vertex_layout_ = std::make_unique<VertexLayout>();
  index_buffer_ = std::make_unique<IndexBuffer>(indicies_, sizeof(indicies_));
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
  if ((verticies_[0].coords.z == verticies_[1].coords.z) &&
      (verticies_[2].coords.z == verticies_[3].coords.z) &&
      (verticies_[1].coords.z == verticies_[2].coords.z))
    return verticies_[0].coords.z;
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
  verticies_[0] = right.verticies_[0];
  verticies_[1] = right.verticies_[1];
  verticies_[2] = right.verticies_[2];
  verticies_[3] = right.verticies_[3];
  shader_program_ = right.shader_program_;
  std::cout << "[Moved] GameObject " << id_ << std::endl;
}

GameObject::GameObject(const GameObject& right) {
  id_ = right.id_;
  vertex_buffer_ = std::make_unique<VertexBuffer>(verticies_, sizeof(verticies_));
  vertex_layout_ = std::make_unique<VertexLayout>();
  index_buffer_ = std::make_unique<IndexBuffer>(indicies_, sizeof(indicies_));
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
  verticies_[0] = right.verticies_[0];
  verticies_[1] = right.verticies_[1];
  verticies_[2] = right.verticies_[2];
  verticies_[3] = right.verticies_[3];
  shader_program_ = right.shader_program_;
  std::cout << "[Copied] GameObject " << id_ << std::endl;
}

GameObject& GameObject::operator=(const GameObject& right) {
  id_ = right.id_;
  model_mtx_ = right.model_mtx_;
  verticies_[0] = right.verticies_[0];
  verticies_[1] = right.verticies_[1];
  verticies_[2] = right.verticies_[2];
  verticies_[3] = right.verticies_[3];
  shader_program_ = right.shader_program_;

  return *this;
}

bool GameObject::operator<(const GameObject& right) {
  if ((this->verticies_[0].coords.z < right.verticies_[0].coords.z) &&
      (this->verticies_[1].coords.z < right.verticies_[1].coords.z) &&
      (this->verticies_[2].coords.z < right.verticies_[2].coords.z) &&
      (this->verticies_[3].coords.z < right.verticies_[3].coords.z))
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
