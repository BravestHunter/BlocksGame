#pragma once

#include "chunk_part.hpp"


struct Chunk
{
  const static size_t PartsNumber = 16;
  const static size_t BlocksNumber = PartsNumber * ChunkPart::BlocksNumber;

  ChunkPart parts[PartsNumber];

  bool operator==(const Chunk& other) const
  {
    return std::memcmp(&parts, &other.parts, PartsNumber * sizeof(ChunkPart));
  }
};
