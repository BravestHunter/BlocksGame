#pragma once

#include <cstring>

#include "block.hpp"


struct ChunkPart
{
  const static size_t Length = 16;
  const static size_t Width = 16;
  const static size_t Height = 16;
  const static size_t BlocksNumber = Length * Width * Height;

  Block blocks[BlocksNumber];

  bool operator==(const ChunkPart& other) const
  {
    return std::memcmp(&blocks, &other.blocks, BlocksNumber * sizeof(Block));
  }
};
