#include "world.hpp"


World::World()
{

}

World::~World()
{

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
  for (int i = 0; i < Chunk::PartsNumber; i++)
  {
    ChunkPart& part = chunk->parts[i];

    for (int j = 0; j < ChunkPart::BlocksNumber; j++)
    {
      part.blocks[j] = rand() % 3;
    }
  }

  return chunk;
}


void World::SaveChunkToFile(const Chunk* chunk)
{

}
