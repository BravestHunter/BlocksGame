#pragma once

#include <glm/glm.hpp>

#include "image.hpp"


/// <summary>
/// Represents character glyph.
/// </summary>
struct Glyph
{
  Image texture {};
  glm::ivec2 bearing {};
  glm::ivec2 advance {};
};
