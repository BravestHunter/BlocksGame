#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "container.hpp"

#include "camera.hpp"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

namespace blocks_game
{
  class Game
  {
  public:
    Game();
    ~Game();

    OpResult Run();

    Camera& GetCamera() const;
    float GetLastX() const;
    void SetLastX(float value);
    float GetLastY() const;
    void SetLastY(float value);
    bool IsFirstMouse() const;
    void SetFirstMouse(bool value);

  private:
    ContainerCleanup _containerCleanup;

    Camera& camera = Camera();
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void ProcessInput(GLFWwindow* window);
  };
}
