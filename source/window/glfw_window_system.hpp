#pragma once

#include <GLFW/glfw3.h>

#include "abstract_window_system.hpp"


class GlfwWindowSystem : public AbstractWindowSystem
{
public:
  GlfwWindowSystem(unsigned int width, unsigned int height);
  virtual ~GlfwWindowSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual void SwapBuffers() override;
  virtual void RequestClose() override;

  virtual bool IsCloseRequested() const override;
  virtual unsigned int GetWidth() override;
  virtual unsigned int GetHeight() override;

  GLFWwindow* GetGlfwWindow();

  friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
  GLFWwindow* _window;
  unsigned int _width;
  unsigned int _height;
};
