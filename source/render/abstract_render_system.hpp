#pragma once

#include "abstract_system.hpp"
#include "camera.hpp"


class AbstractRenderSystem : public AbstractSystem
{
public:
  virtual void RenderScene() = 0;

  virtual void SetViewport(unsigned int width, unsigned int height) = 0;

  virtual Camera* GetCamera() = 0;
};
