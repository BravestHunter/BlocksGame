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
  const static size_t FaceVerticesNumber = 4;
  const static size_t FaceIndicesNumber = 6;

  const static size_t BlockVerticesNumber = FaceVerticesNumber * 6;
  const static size_t BlockIndicesNumber = FaceIndicesNumber *  6;

  const static size_t ChunkPartVerticesNumber = BlockVerticesNumber * ChunkPart::BlocksNumber;
  const static size_t ChunkPartIndicesNumber = BlockIndicesNumber * ChunkPart::BlocksNumber;

  const static size_t ChunkVerticesNumber = ChunkPartVerticesNumber * Chunk::PartsNumber;
  const static size_t ChunkIndicesNumber = ChunkPartIndicesNumber * Chunk::PartsNumber;

  const static size_t VertexSize = sizeof(float) * 5;
  const static size_t IndexSize = sizeof(unsigned int);

  const static size_t ChunkPartVerticesSize = VertexSize * ChunkPartVerticesNumber;
  const static size_t ChunkPartIndicesSize = IndexSize * ChunkPartIndicesNumber;

  const static size_t ChunkVerticesSize = VertexSize * ChunkVerticesNumber;
  const static size_t ChunkIndicesSize = IndexSize * ChunkIndicesNumber;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;

  GLsizei count[Chunk::PartsNumber];
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
