#pragma once

#include <unordered_map>

#include "chunk.hpp"
#include "chunk_position.hpp"


struct ChunkPositionHasher
{
  std::size_t operator()(const ChunkPosition& key) const
  {
    std::size_t hash = 17;
    hash = hash * 31 + std::hash<int>()(key.position.x);
    hash = hash * 31 + std::hash<int>()(key.position.y);
    return hash;
  }
};


typedef std::unordered_map<ChunkPosition, Chunk*, ChunkPositionHasher> ChunkStorage;
