#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "abstract_render_system.hpp"
#include "shader.hpp"

class GlewRenderSystem : public AbstractRenderSystem
{
public:
  GlewRenderSystem();
  virtual ~GlewRenderSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual void RenderScene() override;

  virtual void SetViewport(unsigned int width, unsigned int height) override;

  virtual Camera* GetCamera() override;

private:
  unsigned int _width;
  unsigned int _height;
  Camera* _camera;
  Shader* _shader;
};
