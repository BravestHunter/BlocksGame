#pragma once

#include <map>
#include <unordered_map>

#include "render/abstract_render_system.hpp"
#include "glew_headers.hpp"
#include "glew_texture.hpp"
#include "glew_glyph.hpp"

#include "glew_shader.hpp"
#include "glew_shader_program.hpp"
#include "glew_block_shader_program.hpp"
#include "glew_chunks_map.hpp"

#include "world/world.hpp"


class GlewRenderSystem : public AbstractRenderSystem
{
public:
  GlewRenderSystem();
  virtual ~GlewRenderSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual void RenderString(std::string text, float x, float y, glm::vec3 color) override;
  virtual void RenderAxes() override;

  virtual void SetViewport(unsigned int width, unsigned int height) override;

  virtual Camera* GetCamera() override;

  virtual void Clear(glm::vec4 color) override;

  virtual OpResult LoadChunk(int x, int y, Chunk* chunk) override;
  virtual OpResult UnloadChunk(int x, int y) override;
  virtual void RenderChunks() override;

private:
  unsigned int _width;
  unsigned int _height;
  Camera* _camera;

  GlewChunksStorage _chunks {};
  GlewTexture* _blockTexture;
  GlewBlockShaderProgram* _blocksShaderProgram;

  std::map<GLchar, GlewGlyph*> _characters;
  GLuint _glyphVAO;
  GLuint _glyphVBO;
  GlewShaderProgram* _glyphShaderProgram;

  unsigned int _axesVBO;
  unsigned int _axesVAO;
  GlewShaderProgram* _axesShaderProgram;
};
