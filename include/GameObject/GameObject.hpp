#pragma once

#include <memory>
#include <array>

#include "Core.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Event.hpp"

namespace fae {

struct GameVertex {
  point3_t coords;
  color_t color;
  point2_t tex_coords;

  GameVertex() {
    coords = {0., 0., 0.};
    color = {0., 0., 0.};
    tex_coords = {0., 0.};
  }
};

class ModelMtx {
 public:
  glm::mat4 translation;
  glm::mat4 rotation;
  glm::mat4 scale;

  ModelMtx() {
    translation = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
  }

  [[nodiscard]] glm::mat4 GetModelMtx() const {
    return translation * rotation * scale;
  }
};

typedef struct GameVertex vertex_t;

class GameObject: public IEventListener {
 public:
  /* Sets up default vertex buffer layout, texture coords,
     creates VAO and VBO, uses default IBO */
  GameObject() noexcept;

  GameObject(GameObject&& right);

  GameObject(const GameObject& right);

  GameObject& operator=(const GameObject&);

  bool operator<(const GameObject& right);

  void SetTextureCoords(point2_t rt, point2_t rb, point2_t lb, point2_t lt);

  void SetCoords(point3_t rt, point3_t rb, point3_t lb, point3_t lt);

  void SetCoords(point3_t lb, point3_t rt);

  /* Take (0, 0) as a lb point */
  void SetSize(point2_t rt);

  void SetLayer(float z);

  void SetShaderProgram(int shader) { shader_program_ = shader; }

  float GetLayer();

  void Scale(float percent);

  void Scale(point3_t percent);

  void Move(point3_t value);

  void MoveTo(point3_t value);

  /* Set left-bottom point only if p_texture is set */
  void SetCoords(point3_t lb);

  void BindVertexBuffer() const { vertex_buffer_->Bind(); }

  void BindVertexArray() const { vertex_array_->Bind(); }

  void BindIndexBuffer() const { index_buffer_->Bind(); }

  void UnbindVertexBuffer() const { vertex_buffer_->Unbind(); }

  void UnbindVertexArray() const { vertex_array_->Unbind(); }

  void UnbindIndexBuffer() const { index_buffer_->Unbind(); }

  [[nodiscard]] glm::mat4 GetModelMtx() const { return model_mtx_.GetModelMtx(); }

  [[nodiscard]] vertex_t* GetVertexDataPtr() { return verticies_; }

  [[nodiscard]] int GetShaderProgram() const { return shader_program_; }

  [[nodiscard]] game_object_id GetId() const { return id_; }

  virtual void UseShaderProgram() = 0;

  virtual ~GameObject();

 protected:
  game_object_id id_;

  std::unique_ptr<VertexBuffer> vertex_buffer_;
  std::unique_ptr<VertexArray> vertex_array_;
  std::unique_ptr<VertexLayout> vertex_layout_;
  std::unique_ptr<IndexBuffer> index_buffer_;

  int shader_program_;
  ModelMtx model_mtx_;
  vertex_t verticies_[4];
  const GLuint indicies_[6] = {
    0, 1, 3,
    1, 2, 3
  };
/*
  std::array<vertex_t, 4> verticies_;
  const std::array<GLuint, 6> indicies_ = {
    0, 1, 3,
    1, 2, 3
  };
  */
};

}  // namespace fae
