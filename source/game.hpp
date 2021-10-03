#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "container.hpp"

#include "camera.hpp"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;


class Game
{
public:
  Game();
  ~Game();

  OpResult Run();

private:
  ContainerCleanup _containerCleanup;

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  void ProcessInput(AbstractInputSystem* inputSystem, AbstractWindowSystem* windowSystem, Camera* camera);
};
