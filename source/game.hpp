#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "container.hpp"
#include "camera.hpp"
#include "model/model.hpp"

class Game
{
public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  OpResult Run();

private:
  ContainerCleanup _containerCleanup;

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  void ProcessInput(AbstractInputSystem* inputSystem, AbstractWindowSystem* windowSystem, Camera* camera);
};
