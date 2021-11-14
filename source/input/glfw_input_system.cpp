#include "glfw_input_system.hpp"

#include "container.hpp"
#include "window/glfw_window_system.hpp"
#include "glfw_convert.hpp"


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


GlfwInputSystem::GlfwInputSystem()
{
  // Nothing to do here
}

GlfwInputSystem::~GlfwInputSystem()
{
  // Nothing to do here
}


OpResult GlfwInputSystem::Init()
{
  GlfwWindowSystem* windowSystem = dynamic_cast<GlfwWindowSystem*>(Container::GetWindowSystem());
  if (!windowSystem->IsInitialized())
  {
    return FAILURE;
  }

  _window = windowSystem->GetGlfwWindow();

  glfwSetCursorPosCallback(_window, mouse_callback);
  glfwSetScrollCallback(_window, scroll_callback);


  return SUCCESS;
}

OpResult GlfwInputSystem::Deinit()
{
  return SUCCESS;
}


void GlfwInputSystem::ProcessEvents()
{
  glfwPollEvents();
}

KeyState GlfwInputSystem::GetKeyStatus(KeyboardKey key) const
{
  return ConvertFromGlfwKeyState(glfwGetKey(_window, ConvertToGlfwKeyboardKey(key)));
}


float GlfwInputSystem::GetMouseDeltaX()
{
  return _mouseDeltaX;
}

float GlfwInputSystem::GetMouseDeltaY()
{
  return _mouseDeltaY;
}

void GlfwInputSystem::ClearMouseDelta()
{
  _mouseDeltaX = 0;
  _mouseDeltaY = 0;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  static GlfwInputSystem* inputSystem = nullptr;
  static float lastX = 0;
  static float lastY = 0;
  if (inputSystem == nullptr)
  {
    inputSystem = dynamic_cast<GlfwInputSystem*>(Container::GetInputSystem());

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    lastX = width / 2;
    lastY = height / 2;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  inputSystem->_mouseDeltaX += xoffset;
  inputSystem->_mouseDeltaY += yoffset;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  // Nothing to do here
}

