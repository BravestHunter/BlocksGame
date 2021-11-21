#include "glew_glyph.hpp"


GlewGlyph::GlewGlyph(Glyph& glyph) :
  _size(glyph.texture.width, glyph.texture.height), 
  _bearing(glyph.bearing), 
  _advance(glyph.advance)
{
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RED,
    glyph.texture.width,
    glyph.texture.height,
    0,
    GL_RED,
    GL_UNSIGNED_BYTE,
    &glyph.texture.data[0]
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GlewGlyph::~GlewGlyph()
{
  if (_id != GlewEntity::FreeId)
  {
    glDeleteTextures(1, &_id);
  }
}


glm::ivec2 GlewGlyph::GetSize()
{
  return _size;
}

glm::ivec2 GlewGlyph::GetBearing()
{
  return _bearing;
}

glm::ivec2 GlewGlyph::GetAdvance()
{
  return _advance;
}
