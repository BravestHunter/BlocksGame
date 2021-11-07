#pragma once

#include "glew_shader_program.hpp"


class GlewBlockShaderProgram : public GlewShaderProgram
{
public:
  GlewBlockShaderProgram();
  ~GlewBlockShaderProgram();

  void SetViewProjection(const glm::mat4& mat);

  static OpResult Create(GlewBlockShaderProgram** shaderProgram);

private:
  GLint _vpUniformLocation;
};
