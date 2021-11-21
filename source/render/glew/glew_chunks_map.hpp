#pragma once

#include <unordered_map>

#include "glew_headers.hpp"


struct ChunkKey
{
  int x;
  int y;

  bool operator==(const ChunkKey& other) const
  {
    return
      x == other.x &&
      y == other.y;
  }
};


struct ChunkData
{
  GLuint vao;
  GLuint vbo;
};


struct ChunkKeyHasher
{
  std::size_t operator()(const ChunkKey& key) const
  {
    std::size_t hash = 17;
    hash = hash * 31 + std::hash<int>()(key.x);
    hash = hash * 31 + std::hash<int>()(key.y);
    return hash;
  }
};


typedef std::unordered_map<ChunkKey, ChunkData, ChunkKeyHasher> GlewChunksStorage;
