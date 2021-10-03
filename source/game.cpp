#include "game.hpp"

#include <iostream>
#include <string>

#include "Camera.hpp"
#include "Shader.hpp"

#include "file/common_file_system.hpp"
#include "window/glfw_window_system.hpp"
#include "input/glfw_input_system.hpp"
#include "render/glew_render_system.hpp"


Game::Game()
{
  // Set all systems to container
  Container::SetFileSystem(new CommonFileSystem());
  Container::SetWindowSystem(new GlfwWindowSystem(SCR_WIDTH, SCR_HEIGHT));
  Container::SetInputSystem(new GlfwInputSystem());
  Container::SetRenderSystem(new GlewRenderSystem());

  // Initialize systems in correct order
  Container::GetFileSystem()->Init();
  Container::GetWindowSystem()->Init();
  Container::GetInputSystem()->Init();
  Container::GetRenderSystem()->Init();
}

Game::~Game()
{
  // Deinitialize systems in correct order
  Container::GetRenderSystem()->Deinit();
  Container::GetInputSystem()->Deinit();
  Container::GetWindowSystem()->Deinit();
  Container::GetFileSystem()->Deinit();
}

OpResult Game::Run()
{
  AbstractFileSystem* fileSystem = Container::GetFileSystem();
  AbstractWindowSystem* windowSystem = Container::GetWindowSystem();
  AbstractInputSystem* inputSystem = Container::GetInputSystem();
  AbstractRenderSystem* renderSystem = Container::GetRenderSystem();
  Camera* camera = renderSystem->GetCamera();

  renderSystem->SetViewport(SCR_WIDTH, SCR_HEIGHT);

  unsigned int width = SCR_WIDTH;
  unsigned int height = SCR_HEIGHT;
  while (!windowSystem->IsCloseRequested())
  {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ProcessInput(inputSystem, windowSystem, camera);

    renderSystem->RenderScene();

    if (windowSystem->GetWidth() != width ||
        windowSystem->GetHeight() != height)
    {
      width = windowSystem->GetWidth();
      height = windowSystem->GetHeight();

      renderSystem->SetViewport(width, height);
    }

    windowSystem->SwapBuffers();
  }

  return SUCCESS;
}


void Game::ProcessInput(AbstractInputSystem* inputSystem, AbstractWindowSystem* windowSystem, Camera* camera)
{
  inputSystem->ProcessEvents();

  if (inputSystem->GetKeyStatus(KeyboardKey::ESCAPE) == KeyState::PRESSED)
  {
    windowSystem->RequestClose();
  }

  if (inputSystem->GetKeyStatus(KeyboardKey::W) == KeyState::PRESSED)
  {
    camera->ProcessKeyboard(FORWARD, deltaTime);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::S) == KeyState::PRESSED)
  {
    camera->ProcessKeyboard(BACKWARD, deltaTime);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::A) == KeyState::PRESSED)
  {
    camera->ProcessKeyboard(LEFT, deltaTime);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::D) == KeyState::PRESSED)
  {
    camera->ProcessKeyboard(RIGHT, deltaTime);
  }

  if (inputSystem->GetMouseDeltaX() != 0 ||
    inputSystem->GetMouseDeltaY() != 0)
  {
    camera->ProcessMouseMovement(inputSystem->GetMouseDeltaX(), inputSystem->GetMouseDeltaY());
    inputSystem->ClearMouseDelta();
  }
}
