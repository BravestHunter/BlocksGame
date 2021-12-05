#include "game.hpp"

#include <iostream>
#include <string>
#include <cstdarg>

#include "direction.hpp"
#include "Camera.hpp"


std::string string_format(const std::string fmt_str, ...) {
  int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
  std::unique_ptr<char[]> formatted;
  va_list ap;
  while (1) {
    formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
    strcpy(&formatted[0], fmt_str.c_str());
    va_start(ap, fmt_str);
    final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
    va_end(ap);
    if (final_n < 0 || final_n >= n)
      n += abs(final_n - n + 1);
    else
      break;
  }
  return std::string(formatted.get());
}

Game::Game()
{
  // Nothing to do here
}

Game::~Game()
{
  // Nothing to do here
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

  // Initial chunks load
  _lastCenterChunk = glm::ivec2(0, 0);
  int a = _lastCenterChunk.x - _renderRadius;
  for (int i = _lastCenterChunk.x - _renderRadius, lastX = _lastCenterChunk.x + _renderRadius; i <= lastX; i++)
  {
    for (int j = _lastCenterChunk.y - _renderRadius, lastY = _lastCenterChunk.y + _renderRadius; j <= lastY; j++)
    {
      renderSystem->LoadChunk(i, j, _world.GetChunk(i, j));
    }
  }
  
  while (!windowSystem->IsCloseRequested())
  {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ProcessInput(inputSystem, windowSystem, camera);
    //UpdateLoadedChunks(camera->GetPosition());

    renderSystem->Clear(glm::vec4(0.63f, 0.85f, 0.97f, 1.0f));

    renderSystem->RenderChunks();

    renderSystem->RenderAxes();

    // Poor FPS:
    renderSystem->RenderString(std::to_string((int)(1 / deltaTime)), 25.0f, height / 2 - 25.0f, glm::vec3(1.0f, 1.0f, 0.0f));

    // Position:
    std::string positionStr = string_format("%f %f %f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
    renderSystem->RenderString(positionStr, 25.0f, 25.0f, glm::vec3(1.0f, 1.0f, 0.0f));

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
    camera->SetPosition(position + camera->GetForward() * deltaTime * 150.0f);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::S) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position - camera->GetForward() * deltaTime * 150.0f);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::A) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position - camera->GetRight() * deltaTime * 150.0f);
  }
  if (inputSystem->GetKeyStatus(KeyboardKey::D) == KeyboardKeyState::PRESSED)
  {
    camera->SetPosition(position + camera->GetRight() * deltaTime * 150.0f);
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


void Game::UpdateLoadedChunks(const glm::vec3& position)
{
  glm::ivec2 centerChunk = glm::ivec2(position.x / 16, position.y / 16);
  if (centerChunk == _lastCenterChunk)
  {
    return;
  }

  AbstractRenderSystem* renderSystem = Container::GetRenderSystem();

  // Unload chunks
  for (int i = _lastCenterChunk.x - _renderRadius, lastX = _lastCenterChunk.x + _renderRadius; i <= lastX; i++)
  {
    for (int j = _lastCenterChunk.y - _renderRadius, lastY = _lastCenterChunk.y + _renderRadius; j <= lastY; j++)
    {
      if (std::abs(centerChunk.x - i) <= _renderRadius &&
          std::abs(centerChunk.y - j) <= _renderRadius)
      {
        // Chunk still should be loaded
        continue;
      }

      renderSystem->UnloadChunk(i, j);
    }
  }

  // Load chunks
  for (int i = centerChunk.x - _renderRadius, lastX = centerChunk.x + _renderRadius; i <= lastX; i++)
  {
    for (int j = centerChunk.y - _renderRadius, lastY = centerChunk.y + _renderRadius; j <= lastY; j++)
    {
      if (std::abs(_lastCenterChunk.x - i) <= _renderRadius &&
          std::abs(_lastCenterChunk.y - j) <= _renderRadius)
      {
        // Chunk is already loaded
        continue;
      }

      renderSystem->LoadChunk(i, j, _world.GetChunk(i, j));
    }
  }

  _lastCenterChunk = centerChunk;
}
