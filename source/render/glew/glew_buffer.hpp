#pragma once

#include "glew_entity.hpp"


class GlewBuffer : public GlewEntity
{
public:
  GlewBuffer();
  GlewBuffer(const void* data, size_t size, GLuint type, GLenum usage);
  virtual ~GlewBuffer() override;

  void Bind() const;

private:
  size_t _size;
  GLuint _type;
  GLenum _usage;
};
