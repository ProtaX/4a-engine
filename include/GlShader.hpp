#pragma once

#include <string>
#include <string_view>

#include "Core.hpp"

namespace fae {

class GlShader {
 public:
  GlShader() noexcept;

  ~GlShader();

  GLuint LinkFromFiles(std::string_view vertex_file_name, std::string_view fragment_file_name);

  GLuint LinkFromSource(std::string_view vertex_source, std::string_view fragment_source);

  void UseShader() const;

  [[nodiscard]] GLuint GetProgramId() const { return shader_program_; }
  [[nodiscard]] bool IsReady() { return shader_program_ != GL_FALSE; }
  [[nodiscard]] GLint GetAttribLocation(std::string_view name) const;
  [[nodiscard]] GLint GetUniformLocation(std::string_view name) const;

  void SetUniform(GLint location, const glm::vec2& value);
  void SetUniform(GLint location, const glm::vec3& value);
  void SetUniform(GLint location, const glm::vec4& value);

  void SetUniform(GLint location, const glm::mat4& value);
  void SetUniform(GLint location, GLint value);

 private:
  static void PrintInfoLogShader(GLuint shader);

  static void PrintInfoLogProgram(GLuint shader);

  GLuint LoadSourceFile(std::string_view source_file_name, GLuint shader_type);

  GLuint CompileSource(const GLchar* source, GLuint shader_type);

  void LinkProgram();

  GLuint shader_program_;
  GLuint vertex_shader_;
  GLuint fragment_shader_;
};

}  // namespace fae
