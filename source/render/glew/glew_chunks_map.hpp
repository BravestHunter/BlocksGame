#pragma once

#include <unordered_map>

#include "glew_headers.hpp"
#include "glew_vertex_array.hpp"
#include "glew_buffer.hpp"


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
  ChunkData() : _vao(nullptr), _vbo(nullptr)
  {
  }

  ChunkData(GlewVertexArray* vao, GlewBuffer* vbo) : _vao(vao), _vbo(vbo)
  {
  }

  ~ChunkData()
  {
    if (_vao != nullptr)
      delete _vao;

    if (_vbo != nullptr)
      delete _vbo;
  }

  GlewVertexArray* _vao;
  GlewBuffer* _vbo;
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


typedef std::unordered_map<ChunkKey, ChunkData*, ChunkKeyHasher> GlewChunksStorage;
