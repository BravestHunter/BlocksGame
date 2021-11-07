#pragma once

#include "render/abstract_render_system.hpp"
#include "glew.hpp"
#include "glew_shader.hpp"
#include "glew_shader_program.hpp"
#include "glew_block_shader_program.hpp"

class GlewRenderSystem : public AbstractRenderSystem
{
public:
  GlewRenderSystem();
  virtual ~GlewRenderSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual void Render() override;

  virtual void SetViewport(unsigned int width, unsigned int height) override;

  virtual Camera* GetCamera() override;

private:
  unsigned int _width;
  unsigned int _height;
  Camera* _camera;
  GlewBlockShaderProgram* _blocksShaderProgram;
};
