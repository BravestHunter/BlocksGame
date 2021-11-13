#pragma once

#include <string>

#include "abstract_system.hpp"
#include "camera.hpp"

class AbstractRenderSystem : public AbstractSystem
{
public:
  virtual void Render() = 0;
  virtual void RenderString(std::string text, float x, float y, glm::vec3 color) = 0;
  virtual void RenderAxes() = 0;

  virtual void SetViewport(unsigned int width, unsigned int height) = 0;

  virtual Camera* GetCamera() = 0;
};
