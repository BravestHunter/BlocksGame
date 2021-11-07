#include "glew_shader_program.hpp"


GlewShaderProgram::GlewShaderProgram(const GlewShader& vertexShader, const GlewShader& fragmentShader)
{
  _shaderProgram = glCreateProgram();

  glAttachShader(_shaderProgram, vertexShader.GetId());
  glAttachShader(_shaderProgram, fragmentShader.GetId());

  Link();
}

GlewShaderProgram::GlewShaderProgram(const GlewShader& vertexShader, const GlewShader& geometryShader, const GlewShader& fragmentShader) : GlewShaderProgram::GlewShaderProgram(vertexShader, fragmentShader)
{
  _shaderProgram = glCreateProgram();

  glAttachShader(_shaderProgram, vertexShader.GetId());
  glAttachShader(_shaderProgram, geometryShader.GetId());
  glAttachShader(_shaderProgram, fragmentShader.GetId());

  Link();
}

GlewShaderProgram::~GlewShaderProgram()
{
  if (_isLinked)
    glDeleteProgram(_shaderProgram);
}


void GlewShaderProgram::Set()
{
  glUseProgram(_shaderProgram);
}

void GlewShaderProgram::Unset()
{
  glUseProgram(NULL);
}


GLuint GlewShaderProgram::GetId() const
{
  return _shaderProgram;
}

bool GlewShaderProgram::IsLinked() const
{
  return _isLinked;
}


void GlewShaderProgram::SetBool(const std::string& name, bool value) const
{
  glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), (int)value);
}

void GlewShaderProgram::SetInt(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), value);
}

void GlewShaderProgram::SetFloat(const std::string& name, float value) const
{
  glUniform1f(glGetUniformLocation(_shaderProgram, name.c_str()), value);
}

void GlewShaderProgram::SetVec2(const std::string& name, const glm::vec2& value) const
{
  glUniform2fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
}

void GlewShaderProgram::SetVec2(const std::string& name, float x, float y) const
{
  glUniform2f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y);
}

void GlewShaderProgram::SetVec3(const std::string& name, const glm::vec3& value) const
{
  glUniform3fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
}

void GlewShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const
{
  glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
}

void GlewShaderProgram::SetVec4(const std::string& name, const glm::vec4& value) const
{
  glUniform4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
}

void GlewShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
  glUniform4f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
}

void GlewShaderProgram::SetMat2(const std::string& name, const glm::mat2& mat) const
{
  glUniformMatrix2fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GlewShaderProgram::SetMat3(const std::string& name, const glm::mat3& mat) const
{
  glUniformMatrix3fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GlewShaderProgram::SetMat4(const std::string& name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void GlewShaderProgram::Link()
{
  glLinkProgram(_shaderProgram);

  GLint isLinked = 0;
  glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);
  _isLinked = (bool)isLinked;
}
