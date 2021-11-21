#pragma once

#include <glm/glm.hpp>


struct ChunkPosition
{
  glm::ivec2 position;

  bool operator==(const ChunkPosition& other) const
  {
    return position == other.position;
  }
};
