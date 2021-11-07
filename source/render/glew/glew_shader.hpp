#pragma once

#include "glew.hpp"
#include "glew_shader_type.hpp"
#include "container.hpp"


class GlewShader
{
public:
  GlewShader(const char* source, GlewShaderType shaderType);
  ~GlewShader();

  GLuint GetId() const;
  bool IsCompiled() const;

private:
  GLuint _shader;
  bool _isCompiled;

  static GLuint GetNativeShaderType(GlewShaderType shaderType);
};
