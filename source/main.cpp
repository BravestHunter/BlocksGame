#include "game.hpp"

#include "op_result.hpp"

#include "log/console_log_system.hpp"
#include "file/common_file_system.hpp"
#include "resource/resource_system.hpp"
#include "window/glfw_window_system.hpp"
#include "input/glfw/glfw_input_system.hpp"
#include "render/glew/glew_render_system.hpp"

const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;


int main()
{
  ContainerCleanup _containerCleanup;

  // Set all systems to container
  Container::SetLogSystem(new ConsoleLogSystem(LogLevel::Debug));
  Container::SetFileSystem(new CommonFileSystem());
  Container::SetResorceSystem(new ResourceSystem());
  Container::SetWindowSystem(new GlfwWindowSystem(WIDTH, HEIGHT));
  Container::SetInputSystem(new GlfwInputSystem());
  Container::SetRenderSystem(new GlewRenderSystem());

  // Initialize systems in correct order
  Container::GetLogSystem()->Init();
  Container::GetFileSystem()->Init();
  Container::GetResourceSystem()->Init();
  Container::GetWindowSystem()->Init();
  Container::GetInputSystem()->Init();
  Container::GetRenderSystem()->Init();

  Game game;
  OpResult result = game.Run();

  // Deinitialize systems in correct order
  Container::GetRenderSystem()->Deinit();
  Container::GetInputSystem()->Deinit();
  Container::GetWindowSystem()->Deinit();
  Container::GetResourceSystem()->Deinit();
  Container::GetFileSystem()->Deinit();
  Container::GetLogSystem()->Deinit();

  return (int)result;
}
