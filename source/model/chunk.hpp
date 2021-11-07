#pragma once

#include "block.hpp"


struct Chunk
{
  const static size_t Length = 16;
  const static size_t Height = 16;
  const static size_t Width = 16;
  const static size_t BlocksNumber = Length * Height * Width;

  Block blocks[BlocksNumber];
};
