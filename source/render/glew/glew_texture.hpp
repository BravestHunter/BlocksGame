#pragma once

#include "glew_headers.hpp"
#include "glew_entity.hpp"
#include "resource/image.hpp"


class GlewTexture : public GlewEntity
{
public:
  GlewTexture(Image& texture);
  virtual ~GlewTexture() override;

  void Set(GLuint textureSpecifier);
};
