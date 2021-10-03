#include "shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const char* geometryPath)
{
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  std::ifstream gShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try
  {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    if (geometryPath != nullptr)
    {
      gShaderFile.open(geometryPath);
      std::stringstream gShaderStream;
      gShaderStream << gShaderFile.rdbuf();
      geometryCode = gShaderStream.str();
    }
  }
  catch (std::ifstream::failure& e)
  {
    vShaderFile.close();
    fShaderFile.close();
    gShaderFile.close();

    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  unsigned int vertex, fragment;
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");

  unsigned int geometry;
  if (geometryPath != nullptr)
  {
    const char* gShaderCode = geometryCode.c_str();
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    CheckCompileErrors(geometry, "GEOMETRY");
  }

  Id = glCreateProgram();
  glAttachShader(Id, vertex);
  glAttachShader(Id, fragment);
  if (geometryPath != nullptr)
  {
    glAttachShader(Id, geometry);
  }
  glLinkProgram(Id);
  CheckCompileErrors(Id, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  if (geometryPath != nullptr)
  {
    glDeleteShader(geometry);
  }
}

void Shader::Use()
{
  glUseProgram(this->Id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
  glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
  glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
  glUniform2fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
  glUniform2f(glGetUniformLocation(Id, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
  glUniform3fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
  glUniform3f(glGetUniformLocation(Id, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
  glUniform4fv(glGetUniformLocation(Id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
  glUniform4f(glGetUniformLocation(Id, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
  glUniformMatrix2fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
  glUniformMatrix3fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}
