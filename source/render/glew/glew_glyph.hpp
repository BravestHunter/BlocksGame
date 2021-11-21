#pragma once

#include <glm/glm.hpp>

#include "glew_headers.hpp"
#include "glew_texture.hpp"
#include "resource/glyph.hpp"


class GlewGlyph : public GlewEntity
{
public:
  GlewGlyph(Glyph& glyph);
  virtual ~GlewGlyph() override;

  glm::ivec2 GetSize();
  glm::ivec2 GetBearing();
  glm::ivec2 GetAdvance();

private:
  glm::ivec2 _size;
  glm::ivec2 _bearing;
  glm::ivec2 _advance;
};
