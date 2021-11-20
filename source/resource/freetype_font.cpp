#include "freetype_font.hpp"


FreetypeFont::FreetypeFont(FT_Face face) : _freetypeFace(face)
{
  FT_Set_Pixel_Sizes(_freetypeFace, 0, _actualHeight);
}

FreetypeFont::~FreetypeFont()
{
  FT_Done_Face(_freetypeFace);
}


OpResult FreetypeFont::GetGlyph(unsigned long charCode, Glyph& glyph, unsigned int height)
{
  if (_actualHeight != height)
  {
    FT_Set_Pixel_Sizes(_freetypeFace, 0, height);
    _actualHeight = height;
  }

  if (FT_Load_Char(_freetypeFace, charCode, FT_LOAD_RENDER))
  {
    return FAILURE;
  }

  assert(_freetypeFace->glyph->bitmap.pitch > 0);

  glyph.texture.width = _freetypeFace->glyph->bitmap.width;
  glyph.texture.height = _freetypeFace->glyph->bitmap.rows;
  glyph.texture.channels = _freetypeFace->glyph->bitmap.width / _freetypeFace->glyph->bitmap.pitch;

  size_t size = glyph.texture.width * glyph.texture.height * glyph.texture.channels;
  glyph.texture.data = std::vector<Byte>(size);
  memcpy(&glyph.texture.data[0], _freetypeFace->glyph->bitmap.buffer, size);

  glyph.bearing = glm::ivec2(_freetypeFace->glyph->bitmap_left, _freetypeFace->glyph->bitmap_top);
  glyph.advance = glm::ivec2(_freetypeFace->glyph->advance.x, _freetypeFace->glyph->advance.y);

  return SUCCESS;
}
