#include "glew_render_system.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "resource/glyph.hpp"
#include "container.hpp"

#define GLYPH_VERTEX_SHADER "/glyph.vs"
#define GLYPH_FRAGMENT_SHADER "/glyph.fs"
#define AXES_VERTEX_SHADER "/axes.vs"
#define AXES_FRAGMENT_SHADER "/axes.fs"

#define GLYPH_VERTEX_SHADER_PATH SHADERS_DIRECTORY GLYPH_VERTEX_SHADER
#define GLYPH_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY GLYPH_FRAGMENT_SHADER
#define AXES_VERTEX_SHADER_PATH SHADERS_DIRECTORY AXES_VERTEX_SHADER
#define AXES_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY AXES_FRAGMENT_SHADER

#define AXES_FONTS_PATH RESOURCE_DIRECTORY "/fonts"
#define QUICKSAND_FONT "/aller/Aller_Rg.ttf"
#define QUICKSAND_FONTPATH AXES_FONTS_PATH QUICKSAND_FONT


GlewRenderSystem::GlewRenderSystem() : _width(0), _height(0), _camera(NULL), _blocksShaderProgram(NULL)
{
  _camera = new Camera(
    CameraProjectionType::Perspective,
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(8.0f, 8.0f, 256.0f),
    0.0f,
    0.0
  );
}

GlewRenderSystem::~GlewRenderSystem()
{
  delete _camera;

  delete _blocksShaderProgram;
  delete _glyphShaderProgram;
  delete _axesShaderProgram;
}


OpResult GlewRenderSystem::Init()
{
  if (_isInitialized)
  {
    // Double initialize is not allowed
    return FAILURE;
  }

  AbstractFileSystem* fileSystem = Container::GetFileSystem();
  AbstractResourceSystem* resourceSystem = Container::GetResourceSystem();

  glewExperimental = GL_TRUE;
  glewInit();

  _blocksShaderProgram = new GlewBlockShaderProgram();
  if (!_blocksShaderProgram->IsLinked())
  {
    return FAILURE;
  }

  std::string source;
  fileSystem->ReadString(GLYPH_VERTEX_SHADER_PATH, source);
  GlewShader glyphVertexShader(source.c_str(), GlewShaderType::Vertex);
  fileSystem->ReadString(GLYPH_FRAGMENT_SHADER_PATH, source);
  GlewShader glyphFragmentShader(source.c_str(), GlewShaderType::Fragment);
  _glyphShaderProgram = new GlewShaderProgram(glyphVertexShader, glyphFragmentShader);
  if (!_glyphShaderProgram->IsLinked())
  {
    return FAILURE;
  }

  fileSystem->ReadString(AXES_VERTEX_SHADER_PATH, source);
  GlewShader axesVertexShader(source.c_str(), GlewShaderType::Vertex);
  fileSystem->ReadString(AXES_FRAGMENT_SHADER_PATH, source);
  GlewShader axesFragmentShader(source.c_str(), GlewShaderType::Fragment);
  _axesShaderProgram = new GlewShaderProgram(axesVertexShader, axesFragmentShader);
  if (!_axesShaderProgram->IsLinked())
  {
    return FAILURE;
  }

  //================================

  Image blockTextureAltlas;
  if (resourceSystem->GetImage("Tex_BlockAtlas", blockTextureAltlas) == FAILURE)
  {
    return FAILURE;
  }
  _blockTextureAltlas = new GlewTexture(blockTextureAltlas);

  //================================

  AbstractFont* font = nullptr;
  if (resourceSystem->GetFont("Font_Aller", &font) == FAILURE)
  {
    return FAILURE;
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  for (int i = 33; i < 127; i++)
  {
    Glyph glyph;
    if (font->GetGlyph(i, glyph, 24) == FAILURE)
    {
      return FAILURE;
    }

    _characters[i] = new GlewGlyph(glyph);
  }

  delete font;

  glGenVertexArrays(1, &_glyphVAO);
  glGenBuffers(1, &_glyphVBO);
  glBindVertexArray(_glyphVAO);
  glBindBuffer(GL_ARRAY_BUFFER, _glyphVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  //================================

  float axesData[] = {
    0.0, 0.0, 0.0,      1.0, 0.0, 0.0,
    10000.0, 0.0, 0.0,  1.0, 0.0, 0.0,

    0.0, 0.0, 0.0,      0.0, 1.0, 0.0,
    0.0, 10000.0, 0.0,  0.0, 1.0, 0.0,

    0.0, 0.0, 0.0,      0.0, 0.0, 1.0,
    0.0, 0.0, 10000.0,  0.0, 0.0, 1.0
  };

  glGenVertexArrays(1, &_axesVAO);
  glGenBuffers(1, &_axesVBO);
  glBindVertexArray(_axesVAO);
  glBindBuffer(GL_ARRAY_BUFFER, _axesVBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(axesData), axesData, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //================================

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  _isInitialized = true;
  return SUCCESS;
}

OpResult GlewRenderSystem::Deinit()
{
  if (!_isInitialized)
  {
    return FAILURE;
  }

  delete _blockTextureAltlas;

  for (const auto& chunk : _chunks)
  {
    glDeleteVertexArrays(1, &chunk.second.vao);
    glDeleteBuffers(1, &chunk.second.vbo);
  }

  for (const auto& glyph : _characters)
  {
    delete glyph.second;
  }

  //================================
  glDeleteVertexArrays(1, &_glyphVAO);
  glDeleteBuffers(1, &_glyphVBO);
  //================================
  glDeleteVertexArrays(1, &_axesVAO);
  glDeleteBuffers(1, &_axesVBO);
  //================================

  _isInitialized = false;
  return SUCCESS;
}


void GlewRenderSystem::RenderString(std::string text, float x, float y, glm::vec3 color)
{
  float scale = 1.0f;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _glyphShaderProgram->Set();

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
  _glyphShaderProgram->SetMat4("projection", projection);

  glUniform3f(glGetUniformLocation(_glyphShaderProgram->GetId(), "textColor"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(_glyphVAO);

  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    if (*c == 32)
    {
      x += 5.0;
      continue;
    }

    GlewGlyph& glyph = *_characters[*c];

    GLfloat xpos = x + glyph.GetBearing().x * scale;
    GLfloat ypos = y - (glyph.GetSize().y - glyph.GetBearing().y) * scale;
    //GLfloat ypos = y + (glyph.GetSize().y - glyph.GetBearing().y) * scale;

    GLfloat w = glyph.GetSize().x * scale;
    GLfloat h = glyph.GetSize().y * scale;
    // Update VBO for each character
    GLfloat vertices[6][4] = {
        { xpos, ypos + h, 0.0, 0.0 },
        { xpos, ypos, 0.0, 1.0 },
        { xpos + w, ypos, 1.0, 1.0 },
        { xpos, ypos + h, 0.0, 0.0 },
        { xpos + w, ypos, 1.0, 1.0 },
        { xpos + w, ypos + h, 1.0, 0.0 }
    };
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, glyph.GetId());
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, _glyphVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (glyph.GetAdvance().x >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

}

void GlewRenderSystem::RenderAxes()
{
  _axesShaderProgram->Set();

  glm::mat4 view = _camera->GetView();
  glm::mat4 projection = _camera->GetProjection();

  _axesShaderProgram->SetMat4("projection", projection);
  _axesShaderProgram->SetMat4("view", view);

  // Draw
  glBindVertexArray(_axesVAO);
  glDrawArrays(GL_LINES, 0, 6);
}


void GlewRenderSystem::SetViewport(unsigned int width, unsigned int height)
{
  glViewport(0, 0, width, height);

  _width = width;
  _height = height;
}


Camera* GlewRenderSystem::GetCamera()
{
  return _camera;
}


void GlewRenderSystem::Clear(glm::vec4 color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


OpResult GlewRenderSystem::LoadChunk(int x, int y, Chunk* chunk)
{
  const ChunkKey key { x, y };

  if (_chunks.contains(key))
  {
    return FAILURE;
  }

  ChunkData chunkData;
  glGenVertexArrays(1, &chunkData.vao);
  glGenBuffers(1, &chunkData.vbo);

  glBindVertexArray(chunkData.vao);
  glBindBuffer(GL_ARRAY_BUFFER, chunkData.vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(chunk->parts), chunk->parts, GL_STATIC_DRAW);
  glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  _chunks[key] = chunkData;

  return SUCCESS;
}

OpResult GlewRenderSystem::UnloadChunk(int x, int y)
{
  const ChunkKey key { x, y };

  const auto chunk = _chunks.find(key);

  if (chunk == _chunks.end())
  {
    return FAILURE;
  }

  glDeleteVertexArrays(1, &chunk->second.vao);
  glDeleteBuffers(1, &chunk->second.vbo);

  _chunks.erase(chunk);

  return SUCCESS;
}

void GlewRenderSystem::RenderChunks()
{
  _blocksShaderProgram->Set();

  _blockTextureAltlas->Set(GL_TEXTURE_2D);

  glm::mat4 view = _camera->GetView();
  glm::mat4 projection = _camera->GetProjection();
  glm::mat4 viewProjection = projection * view;
  _blocksShaderProgram->SetViewProjection(viewProjection);

  for (const auto& chunk : _chunks)
  {
    const ChunkKey& chunkKey = chunk.first;
    const ChunkData& chunkData = chunk.second;

    _blocksShaderProgram->SetInt("xOffset", chunkKey.x * 16);
    _blocksShaderProgram->SetInt("yOffset", chunkKey.y * 16);

    glBindVertexArray(chunkData.vao);
    glDrawArrays(GL_POINTS, 0, Chunk::BlocksNumber);
  }
}
