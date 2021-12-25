#pragma once

#include "block.hpp"


struct Chunk
{
  const static size_t Length = 16;
  const static size_t Width = 16;
  const static size_t Height = 256;

  const static size_t Layer = Length * Width;
  const static size_t BlocksNumber = Length * Width * Height;

  Block blocks[BlocksNumber];

  bool operator==(const Chunk& other) const
  {
    return std::memcmp(&blocks, &other.blocks, BlocksNumber * sizeof(Block));
  }
};
