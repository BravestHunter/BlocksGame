#include "game.hpp"

#include <iostream>
#include <string>

#include "direction.hpp"
#include "Camera.hpp"
#include "render/glew/glew_shader.hpp"

#include "file/common_file_system.hpp"
#include "resource/resource_system.hpp"
#include "window/glfw_window_system.hpp"
#include "input/glfw/glfw_input_system.hpp"
#include "render/glew/glew_render_system.hpp"


Game::Game(unsigned int width, unsigned int height)
{
  // Set all systems to container
  Container::SetFileSystem(new CommonFileSystem());
  Container::SetResorceSystem(new ResourceSystem());
  Container::SetWindowSystem(new GlfwWindowSystem(width, height));
  Container::SetInputSystem(new GlfwInputSystem());
  Container::SetRenderSystem(new GlewRenderSystem());

  // Initialize systems in correct order
  Container::GetFileSystem()->Init();
  Container::GetResourceSystem()->Init();
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
  Container::GetResourceSystem()->Deinit();
  Container::GetFileSystem()->Deinit();
}

OpResult Game::Run()
{
  AbstractFileSystem* fileSystem = Container::GetFileSystem();
  AbstractWindowSystem* windowSystem = Container::GetWindowSystem();
  AbstractInputSystem* inputSystem = Container::GetInputSystem();
  AbstractRenderSystem* renderSystem = Container::GetRenderSystem();
  Camera* camera = renderSystem->GetCamera();

  unsigned int width = windowSystem->GetWidth();
  unsigned int height = windowSystem->GetHeight();
  renderSystem->SetViewport(windowSystem->GetWidth(), windowSystem->GetHeight());


  // Add sample chunk
  Chunk* chunk = new Chunk();
  for (int i = 0; i < Chunk::PartsNumber; i++)
  {
    ChunkPart& part = chunk->parts[i];
  
    for (int j = 0; j < ChunkPart::BlocksNumber; j++)
    {
      part.blocks[j] = rand() % 4 > 0 ? 0 : 1;
    }
  }
  //for (int i = 0; i < Chunk::PartsNumber; i++)
  //{
  //  ChunkPart& part = chunk->parts[i];
  //
  //  for (int j = 0; j < ChunkPart::BlocksNumber; j++)
  //  {
  //    part.blocks[j] = 1;
  //  }
  //}

  int halfSize = 4;
  for (int i = -halfSize; i < halfSize; i++)
  {
    for (int j = -halfSize; j < halfSize; j++)
    {
      renderSystem->LoadChunk(i,j, chunk);
    }
  }

  while (!windowSystem->IsCloseRequested())
  {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ProcessInput(inputSystem, windowSystem, camera);

    renderSystem->Clear(glm::vec4(0.63f, 0.85f, 0.97f, 1.0f));

    renderSystem->RenderChunks();

    renderSystem->RenderAxes();

    // Poor FPS:
    renderSystem->RenderString(std::to_string((int)(1 / deltaTime)), 25.0f, 25.0f, glm::vec3(1.0f, 1.0f, 0.0f));

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

  if (inputSystem->GetKeyStatus(KeyboardKey::ESCAPE) == KeyboardKeyState::PRESSED)
  {
    windowSystem->RequestClose();
  }

  glm::vec3 position = camera->GetPosition();
  if (inputSystem->GetKeyStatus(KeyboardKey::W) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position + camera->GetForward() * deltaTime * 50.0f);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::S) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position - camera->GetForward() * deltaTime * 50.0f);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::A) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position - camera->GetRight() * deltaTime * 50.0f);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::D) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position + camera->GetRight() * deltaTime * 50.0f);
  }

  if (inputSystem->GetMouseDeltaX() != 0)
  {
    camera->SetYaw(camera->GetYaw() - inputSystem->GetMouseDeltaX() * 0.1f);
  }
  if (inputSystem->GetMouseDeltaY() != 0)
  {
    camera->SetPitch(camera->GetPitch() + inputSystem->GetMouseDeltaY() * 0.1f);
  }

  inputSystem->ClearMouseDelta();
}
