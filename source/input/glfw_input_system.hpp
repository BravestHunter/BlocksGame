#pragma once

#include <GLFW/glfw3.h>

#include "abstract_input_system.hpp"


class GlfwInputSystem : public AbstractInputSystem
{
public:
  GlfwInputSystem();
  virtual ~GlfwInputSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual void ProcessEvents() override;

  virtual KeyState GetKeyStatus(KeyboardKey key) const override;

  virtual float GetMouseDeltaX() override;
  virtual float GetMouseDeltaY() override;
  virtual void ClearMouseDelta() override;

  friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
  friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
  GLFWwindow* _window;

  float _mouseDeltaX;
  float _mouseDeltaY;
};
