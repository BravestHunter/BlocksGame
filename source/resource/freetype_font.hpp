#pragma once

#include "freetype_headers.hpp"

#include "abstract_font.hpp"


/// <summary>
/// Represents Freetype based font.
/// Generating glyphs on each request.
/// </summary>
class FreetypeFont : public AbstractFont
{
public:
  FreetypeFont(FT_Face face);
  virtual ~FreetypeFont() override;

  virtual OpResult GetGlyph(unsigned long charCode, Glyph& glyph, unsigned int height) override;

private:
  FT_Face _freetypeFace = nullptr;
  unsigned int _actualHeight = 16;
};
