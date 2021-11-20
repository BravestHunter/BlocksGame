#pragma once

#include "op_result.hpp"
#include "glyph.hpp"


/// <summary>
/// Represents some glyph-providing entity.
/// </summary>
class AbstractFont
{
public:
  AbstractFont() = default;
  virtual ~AbstractFont() = default;

  virtual OpResult GetGlyph(unsigned long charCode, Glyph& glyph, unsigned int height) = 0;
};
