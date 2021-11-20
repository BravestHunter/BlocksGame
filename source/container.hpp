#pragma once

#include "file/abstract_file_system.hpp"
#include "resource/abstract_resource_system.hpp"
#include "window/abstract_window_system.hpp"
#include "input/abstract_input_system.hpp"
#include "render/abstract_render_system.hpp"


class Container
{
public:
  static void SetFileSystem(AbstractFileSystem* fileSystem);
  static void SetResorceSystem(AbstractResourceSystem* resourceSystem);
  static void SetWindowSystem(AbstractWindowSystem* windowSystem);
  static void SetInputSystem(AbstractInputSystem* inputSystem);
  static void SetRenderSystem(AbstractRenderSystem* renderSystem);

  static AbstractFileSystem* GetFileSystem();
  static AbstractResourceSystem* GetResourceSystem();
  static AbstractWindowSystem* GetWindowSystem();
  static AbstractInputSystem* GetInputSystem();
  static AbstractRenderSystem* GetRenderSystem();

  static bool IsReady();
  static void CleanUp();

private:
  static AbstractFileSystem* _fileSystem;
  static AbstractResourceSystem* _resourceSystem;
  static AbstractWindowSystem* _windowSystem;
  static AbstractInputSystem* _inputSystem;
  static AbstractRenderSystem* _renderSystem;
};

class ContainerCleanup
{
public:
  ContainerCleanup() = default;
  ~ContainerCleanup();
};
