#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "container.hpp"
#include "camera.hpp"
#include "world/chunk.hpp"
#include "world/world.hpp"

class Game
{
public:
  Game();
  ~Game();

  OpResult Run();

private:
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  World _world;
  unsigned int _renderRadius = 7;
  glm::ivec2 _lastCenterChunk {};

  void ProcessInput(AbstractInputSystem* inputSystem, AbstractWindowSystem* windowSystem, Camera* camera);

  void UpdateLoadedChunks(const glm::vec3& position);
};
