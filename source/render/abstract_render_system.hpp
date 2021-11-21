#pragma once

#include <string>

#include "abstract_system.hpp"
#include "camera.hpp"
#include "world/world.hpp"

class AbstractRenderSystem : public AbstractSystem
{
public:
  virtual void RenderString(std::string text, float x, float y, glm::vec3 color) = 0;
  virtual void RenderAxes() = 0;

  virtual void SetViewport(unsigned int width, unsigned int height) = 0;

  virtual Camera* GetCamera() = 0;

  virtual void Clear(glm::vec4 color) = 0;

  virtual OpResult LoadChunk(int x, int y, Chunk* chunk) = 0;
  virtual OpResult UnloadChunk(int x, int y) = 0;
  virtual void RenderChunks() = 0;
};
