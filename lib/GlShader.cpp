#include "GlShader.hpp"

#include <iostream>
#include <fstream>
#include <array>

namespace fae {

GlShader::GlShader() noexcept: shader_program_(0) { }

GlShader::~GlShader() {
  glUseProgram(0);
  glDeleteShader(vertex_shader_);
  glDeleteShader(fragment_shader_);
  glDeleteShader(shader_program_);
}

GLuint GlShader::LinkFromFiles(std::string_view vertex_file_name, std::string_view fragment_file_name) {
  vertex_shader_ = LoadSourceFile(vertex_file_name, GL_VERTEX_SHADER);
  fragment_shader_ = LoadSourceFile(fragment_file_name, GL_FRAGMENT_SHADER);
  LinkProgram();
  return shader_program_;
}

GLuint GlShader::LinkFromSource(std::string_view vertex_source, std::string_view fragment_source) {
  vertex_shader_ = CompileSource(vertex_source.data(), GL_VERTEX_SHADER);
  fragment_shader_ = CompileSource(fragment_source.data(), GL_FRAGMENT_SHADER);
  LinkProgram();
  return shader_program_;
}

void GlShader::LinkProgram() {
  GLint is_link_ok = GL_FALSE;
  if (!vertex_shader_ || !fragment_shader_) {
    shader_program_ = GL_FALSE;
    return;
  }

  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertex_shader_);
  glAttachShader(shader_program_, fragment_shader_);
  glLinkProgram(shader_program_);
  glGetProgramiv(shader_program_, GL_LINK_STATUS, &is_link_ok);

  if (!is_link_ok) {
    std::cout << "glLinkProgram: ";
    PrintInfoLogShader(shader_program_);
    shader_program_ = GL_FALSE;
    return;
  }
}

void GlShader::UseShader() const {
  glUseProgram(shader_program_);
}

GLuint GlShader::CompileSource(const GLchar* source, GLuint shader_type) {
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  PrintInfoLogShader(shader);
  return shader;
}

GLuint GlShader::LoadSourceFile(std::string_view source_file_name, GLuint shader_type) {
  const char* path = source_file_name.data();
  std::ifstream m_shader(path);
  if (!m_shader) {
    std::cout << source_file_name << " file not found" << std::endl;
    return GL_FALSE;
  }

  std::istreambuf_iterator<char> begin(m_shader), end;
  std::string sourceStr(begin, end);
  m_shader.close();
  return CompileSource (sourceStr.c_str(), shader_type);
}

GLint GlShader::GetAttribLocation(std::string_view name) const {
  return GetAttribLocation(name.data());
}

GLint GlShader::GetUniformLocation(std::string_view name) const {
  GLint location = -1;
  location = glGetUniformLocation(shader_program_, name.data());
  if (location == -1)
    std::cout << "Could not bind uniform" << name << std::endl;
  return location;
}

void GlShader::SetUniform(GLint location, const glm::vec4& value) {
  glUniform4fv(location, 1, &value[0]);
}

void GlShader::SetUniform(GLint location, const glm::vec3& value) {
  glUniform3fv(location, 1, &value[0]);
}

void GlShader::SetUniform(GLint location, const glm::vec2& value) {
  glUniform2fv(location, 1, &value[0]);
}

void GlShader::SetUniform(GLint location, const glm::mat4& value) {
  glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void GlShader::SetUniform(GLint location, const GLint value) {
  glUniform1i(location, value);
}

void GlShader::PrintInfoLogShader(GLuint shader) {
  const GLsizei infologLen = 512;
  GLint charsWritten = 0;
  std::array<GLchar, infologLen> infoLog;
  glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog.data());
  std::cout << "ShaderInfoLog: " << infoLog.data() << std::endl;
}

void GlShader::PrintInfoLogProgram(GLuint shader) {
  const GLsizei infologLen = 512;
  GLint charsWritten = 0;
  std::array<GLchar, infologLen> infoLog;
  glGetProgramInfoLog(shader, infologLen, &charsWritten, infoLog.data());
  std::cout << "ProgramInfoLog: " << infoLog.data() << std::endl;
}

}  // namespace fae
