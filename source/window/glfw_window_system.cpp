#include "glfw_window_system.hpp"

#include <container.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


GlfwWindowSystem::GlfwWindowSystem(unsigned int width, unsigned int height)
{
  _width = width;
  _height = height;
}

GlfwWindowSystem::~GlfwWindowSystem()
{
  // Nothing to do here
}


OpResult GlfwWindowSystem::Init()
{
  if (_isInitialized)
  {
    return FAILURE;
  }

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(_width, _height, "BlocksGame", NULL, NULL);
  if (_window == NULL)
  {
    glfwTerminate();
    return FAILURE;
  }

  glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwMakeContextCurrent(_window);

  //glfwSwapInterval(0);

  _isInitialized = true;
  return SUCCESS;
}

OpResult GlfwWindowSystem::Deinit()
{
  if (!_isInitialized)
  {
    return FAILURE;
  }

  glfwDestroyWindow(_window);
  glfwTerminate();

  _isInitialized = false;
  return SUCCESS;
}


void GlfwWindowSystem::SwapBuffers()
{
  glfwSwapBuffers(_window);
}

void GlfwWindowSystem::RequestClose()
{
  glfwSetWindowShouldClose(_window, true);
}


bool GlfwWindowSystem::IsCloseRequested() const
{
  return glfwWindowShouldClose(_window);
}

unsigned int GlfwWindowSystem::GetWidth()
{
  return _width;
}

unsigned int GlfwWindowSystem::GetHeight()
{
  return _height;
}


GLFWwindow* GlfwWindowSystem::GetGlfwWindow()
{
  return _window;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  static GlfwWindowSystem* windowSystem = nullptr;
  if (windowSystem == nullptr)
  {
    windowSystem = dynamic_cast<GlfwWindowSystem*>(Container::GetWindowSystem());
  }

  windowSystem->_width = width;
  windowSystem->_height = height;
}

