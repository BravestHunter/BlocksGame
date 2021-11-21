#pragma once

#include "glew_headers.hpp"
#include "glew_entity.hpp"
#include "glew_shader_type.hpp"
#include "container.hpp"


class GlewShader : public GlewEntity
{
public:
  GlewShader(const char* source, GlewShaderType shaderType);
  virtual ~GlewShader() override;

  GLuint GetId() const;
  bool IsCompiled() const;

  static OpResult LoadFromFile(const char* path, GlewShaderType shaderType, GlewShader** shader);

private:
  GLuint _shader;
  bool _isCompiled;

  static GLuint GetNativeShaderType(GlewShaderType shaderType);
};
