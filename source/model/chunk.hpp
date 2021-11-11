#pragma once

#include "chunk_part.hpp"


struct Chunk
{
  const static size_t PartsNumber = 16;
  const static size_t BlocksNumber = PartsNumber * ChunkPart::BlocksNumber;

  std::int32_t x;
  std::int32_t y;
  ChunkPart parts[PartsNumber];
};
