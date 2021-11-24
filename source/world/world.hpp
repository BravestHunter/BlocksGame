#pragma once

#include "chunk_storage.hpp"
#include "op_result.hpp"
#include "utils/abstract_noise_2d.hpp"

class World
{
public:
  World();
  ~World();

  Chunk* GetChunk(int x, int y);

private:
  ChunkStorage _chunks {};
  AbstractNoise2D* _noise;

  OpResult LoadChunk(int x, int y);
  OpResult UnloadChunk(int x, int y);

  Chunk* LoadChunkFromFile(const ChunkPosition& position);
  Chunk* GenerateChunk(const ChunkPosition& position);

  void SaveChunkToFile(const Chunk* chunk);
};
