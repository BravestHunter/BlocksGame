#include "world.hpp"

#include "utils/perlin_noise_2d.hpp"


World::World()
{
  _noise = new PerlinNoise2D(rand());
}

World::~World()
{
  delete _noise;
}


Chunk* World::GetChunk(int x, int y)
{
  ChunkPosition position { glm::ivec2(x, y) };

  auto chunkPair = _chunks.find(position);
  if (chunkPair != _chunks.end())
  {
    return chunkPair->second;
  }

  Chunk* chunk = GenerateChunk(position);

  _chunks[position] = chunk;

  return chunk;
}


OpResult World::LoadChunk(int x, int y)
{
  return FAILURE;
}

OpResult World::UnloadChunk(int x, int y)
{
  return FAILURE;
}


Chunk* World::LoadChunkFromFile(const ChunkPosition& position)
{
  return nullptr;
}

Chunk* World::GenerateChunk(const ChunkPosition& position)
{
  Chunk* chunk = new Chunk();

  //for (int i = 0; i < Chunk::PartsNumber; i++)
  //{
  //  ChunkPart& part = chunk->parts[i];
  //
  //  for (int j = 0; j < ChunkPart::BlocksNumber; j++)
  //  {
  //    part.blocks[j] = 1;
  //  }
  //}
  //for (int i = 0; i < Chunk::PartsNumber; i++)
  //{
  //  ChunkPart& part = chunk->parts[i];
  //
  //  for (int j = 0; j < ChunkPart::BlocksNumber; j++)
  //  {
  //    part.blocks[j] = rand() % 4 > 0 ? 0 : 1;
  //  }
  //}
  //for (int i = 0; i < Chunk::PartsNumber; i++)
  //{
  //  ChunkPart& part = chunk->parts[i];
  //
  //  for (int j = 0; j < ChunkPart::BlocksNumber; j++)
  //  {
  //    part.blocks[j] = rand() % 3;
  //  }
  //}

  float* values = new float[256];
  _noise->GetValues(values, position.position.x * 16, position.position.y * 16, 16, 16);

  for (int x = 0; x < Chunk::Length; x++)
  {
    for (int y = 0; y < Chunk::Width; y++)
    {
      int height = (int)((values[x + y * 16] / 2 + 0.5) * Chunk::Height);

      for (int z = 0; z < height; z++)
      {
        int part = z / ChunkPart::Height;
        int h = z - part * ChunkPart::Height;
      
        chunk->parts[part].blocks[x + y * ChunkPart::Length + h * ChunkPart::Layer] = (height > 128 ? 1 : 2);
      }
    }
  }

  delete values;

  return chunk;
}


void World::SaveChunkToFile(const Chunk* chunk)
{

}
