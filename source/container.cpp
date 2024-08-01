 #include "container.hpp"

#include <exception>


void Container::SetFileSystem(AbstractFileSystem* fileSystem)
{
  _fileSystem = fileSystem;
}

void Container::SetResorceSystem(AbstractResourceSystem* resourceSystem)
{
  _resourceSystem = resourceSystem;
}

void Container::SetWindowSystem(AbstractWindowSystem* windowSystem)
{
  _windowSystem = windowSystem;
}

void Container::SetInputSystem(AbstractInputSystem* inputSystem)
{
  _inputSystem = inputSystem;
}

void Container::SetRenderSystem(AbstractRenderSystem* renderSystem)
{
  _renderSystem = renderSystem;
}


AbstractFileSystem* Container::GetFileSystem()
{
  return _fileSystem;
}

AbstractResourceSystem* Container::GetResourceSystem()
{
  return _resourceSystem;
}

AbstractWindowSystem* Container::GetWindowSystem()
{
  return _windowSystem;
}

AbstractInputSystem* Container::GetInputSystem()
{
  return _inputSystem;
}

AbstractRenderSystem* Container::GetRenderSystem()
{
  return _renderSystem;
}


bool Container::IsReady()
{
  return
    _fileSystem != nullptr && _fileSystem->IsInitialized() &&
    _resourceSystem != nullptr && _resourceSystem->IsInitialized() &&
    _windowSystem != nullptr && _windowSystem->IsInitialized() &&
    _inputSystem != nullptr && _inputSystem->IsInitialized() &&
    _renderSystem != nullptr && _renderSystem->IsInitialized();
}

void Container::CleanUp()
{
  delete _fileSystem;
  delete _resourceSystem;
  delete _windowSystem;
  delete _inputSystem;
  delete _renderSystem;
}


AbstractFileSystem* Container::_fileSystem = nullptr;
AbstractResourceSystem* Container::_resourceSystem = nullptr;
AbstractWindowSystem* Container::_windowSystem = nullptr;
AbstractInputSystem* Container::_inputSystem = nullptr;
AbstractRenderSystem* Container::_renderSystem = nullptr;


ContainerCleanup::~ContainerCleanup()
{
  Container::CleanUp();
}
