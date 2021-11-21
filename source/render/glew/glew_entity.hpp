#pragma once

#include "glew_headers.hpp"


class GlewEntity
{
public:
  virtual ~GlewEntity();

  GLuint GetId();

  static const GLuint FreeId = -1;

protected:
  GLuint _id = FreeId;
};
