#pragma once

#include <map>

#include "render/abstract_render_system.hpp"
#include "glew.hpp"
#include "glew_shader.hpp"
#include "glew_shader_program.hpp"
#include "glew_block_shader_program.hpp"

#include "model/model.hpp"


struct Character {
  GLuint     TextureID; // ID текстуры глифа
  glm::ivec2 Size;      // Размеры глифа
  glm::ivec2 Bearing;   // Смещение верхней левой точки глифа
  GLuint     Advance;   // Горизонтальное смещение до начала следующего глифа
};

class GlewRenderSystem : public AbstractRenderSystem
{
public:
  GlewRenderSystem();
  virtual ~GlewRenderSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual void Render() override;
  virtual void RenderString(std::string text, float x, float y, glm::vec3 color) override;

  virtual void SetViewport(unsigned int width, unsigned int height) override;

  virtual Camera* GetCamera() override;

private:
  unsigned int _width;
  unsigned int _height;
  Camera* _camera;

  Chunk* _chunk;

  unsigned int _blocksVBO;
  unsigned int _blocksVAO;
  unsigned int _blockTexture;
  GlewBlockShaderProgram* _blocksShaderProgram;

  std::map<GLchar, Character> _characters;
  GLuint _glyphVAO;
  GLuint _glyphVBO;
  GlewShaderProgram* _glyphShaderProgram;
};
