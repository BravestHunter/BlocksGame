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
  const static size_t ChunkPartsNumber = 16;
  const static size_t ChunkPartBlocksNumber = Chunk::Length * Chunk::Width * 16;

  const static size_t FaceVerticesNumber = 4;
  const static size_t FaceIndicesNumber = 6;
  
  const static size_t BlockVerticesNumber = FaceVerticesNumber * 6;
  const static size_t BlockIndicesNumber = FaceIndicesNumber *  6;
  
  const static size_t ChunkPartVerticesNumber = BlockVerticesNumber * ChunkPartBlocksNumber;
  const static size_t ChunkPartIndicesNumber = BlockIndicesNumber * ChunkPartBlocksNumber;
  
  const static size_t ChunkVerticesNumber = ChunkPartVerticesNumber * ChunkPartsNumber;
  const static size_t ChunkIndicesNumber = ChunkPartIndicesNumber * ChunkPartsNumber;
  
  const static size_t VertexSize = sizeof(float) * 5;
  const static size_t IndexSize = sizeof(unsigned int);
  
  const static size_t ChunkPartVerticesSize = VertexSize * ChunkPartVerticesNumber;
  const static size_t ChunkPartIndicesSize = IndexSize * ChunkPartIndicesNumber;
  
  const static size_t ChunkVerticesSize = VertexSize * ChunkVerticesNumber;
  const static size_t ChunkIndicesSize = IndexSize * ChunkIndicesNumber;

  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;

  GLsizei count[ChunkPartsNumber];
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
