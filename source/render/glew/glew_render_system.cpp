#include "glew_render_system.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "resource/glyph.hpp"
#include "container.hpp"

#define BLOCK_VERTEX_SHADER "/block.vs"
#define BLOCK_FRAGMENT_SHADER "/block.fs"
#define BLOCK_VERTEX_SHADER_PATH SHADERS_DIRECTORY BLOCK_VERTEX_SHADER
#define BLOCK_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY BLOCK_FRAGMENT_SHADER

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


static const float BlockSize = 1.0f;
static const float TexelSize = 0.25;

inline glm::vec3 GetLowBlockPosition(int x, int y, int z, int chunkPart, int chunkX, int chunkY)
{
  return glm::vec3(
    BlockSize * (x + chunkX * 16),
    BlockSize * (y + chunkY * 16),
    BlockSize * (z + chunkPart * 16)
  );
}

glm::vec4 GetTexCoords(unsigned int index)
{
  unsigned int y = index / 4;
  unsigned int x = index - y * 4;

  return glm::vec4(
    x * TexelSize,
    (x + 1) * TexelSize,
    (3.0 - y) * TexelSize,
    (3.0 - y + 1) * TexelSize
  );
}



GlewRenderSystem::GlewRenderSystem() : _width(0), _height(0), _camera(NULL)
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

  std::string source;
  fileSystem->ReadString(BLOCK_VERTEX_SHADER_PATH, source);
  GlewShader blockVertexShader(source.c_str(), GlewShaderType::Vertex);
  fileSystem->ReadString(BLOCK_FRAGMENT_SHADER_PATH, source);
  GlewShader blockFragmentShader(source.c_str(), GlewShaderType::Fragment);
  _blocksShaderProgram = new GlewShaderProgram(blockVertexShader, blockFragmentShader);
  if (!_blocksShaderProgram->IsLinked())
  {
    return FAILURE;
  }

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
    glDeleteVertexArrays(1, &chunk.second._vao);
    glDeleteBuffers(1, &chunk.second._vbo);
    glDeleteBuffers(1, &chunk.second._ebo);
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

  delete _blocksShaderProgram;
  delete _glyphShaderProgram;
  delete _axesShaderProgram;

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

  float* verticesData = new float[ChunkData::ChunkVerticesSize];
  unsigned int* indicesData = new unsigned int[ChunkData::ChunkIndicesSize];
  for (int p = 0; p < Chunk::PartsNumber; p++)
  {
    int vOffset = p * ChunkData::ChunkPartVerticesNumber * 5;
    int iOffset = p * ChunkData::ChunkPartIndicesNumber;

    int iCounter = p * ChunkData::ChunkPartVerticesNumber;
    int iPartCounter = 0;

    for (int z = 0; z < ChunkPart::Height; z++)
    {
      for (int y = 0; y < ChunkPart::Width; y++)
      {
        for (int x = 0; x < ChunkPart::Length; x++)
        {
          int blockIndex = x + y * ChunkPart::Length + z * ChunkPart::Layer;

          // Skip air block
          if (chunk->parts[p].blocks[blockIndex] == 0)
            continue;

          glm::vec3 position = GetLowBlockPosition(x, y, z, p, key.x, key.y);
          glm::vec4 texCoords = GetTexCoords(chunk->parts->blocks[blockIndex] - 1);

          // Front face
          if (x == ChunkPart::Length - 1 || chunk->parts[p].blocks[blockIndex + 1] == 0)
          {
            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[3];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[3];

            indicesData[iOffset++] = iCounter + 0;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 3;
            iCounter += 4;

            iPartCounter += 6;
          }

          // Back face
          if (x == 0 || chunk->parts[p].blocks[blockIndex - 1] == 0)
          {
            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[3];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[3]; 

            indicesData[iOffset++] = iCounter + 0;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 3;
            iCounter += 4;

            iPartCounter += 6;
          }

          // Right face
          if (y == ChunkPart::Width - 1 || chunk->parts[p].blocks[blockIndex + ChunkPart::Width] == 0)
          {
            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[3];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[3];

            indicesData[iOffset++] = iCounter + 0;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 3;
            iCounter += 4;

            iPartCounter += 6;
          }

          // Left face
          if (y == 0 || chunk->parts[p].blocks[blockIndex - ChunkPart::Width] == 0)
          {
            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[3];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[3];

            indicesData[iOffset++] = iCounter + 0;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 3;
            iCounter += 4;

            iPartCounter += 6;
          }

          // Top face
          if (z == ChunkPart::Height - 1 || chunk->parts[p].blocks[blockIndex + ChunkPart::Layer] == 0)
          {
            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[3];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z + BlockSize;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[3];

            indicesData[iOffset++] = iCounter + 0;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 3;
            iCounter += 4;

            iPartCounter += 6;
          }

          // Bottom face
          if (z == 0 || chunk->parts[p].blocks[blockIndex - ChunkPart::Layer] == 0)
          {
            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[2];

            verticesData[vOffset++] = position.x + BlockSize;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[1];
            verticesData[vOffset++] = texCoords[3];

            verticesData[vOffset++] = position.x;
            verticesData[vOffset++] = position.y + BlockSize;
            verticesData[vOffset++] = position.z;
            verticesData[vOffset++] = texCoords[0];
            verticesData[vOffset++] = texCoords[3];

            indicesData[iOffset++] = iCounter + 0;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 2;
            indicesData[iOffset++] = iCounter + 1;
            indicesData[iOffset++] = iCounter + 3;
            iCounter += 4;

            iPartCounter += 6;
          }


        }
      }
    }

    chunkData.count[p] = iPartCounter;
  }

  glGenVertexArrays(1, &chunkData._vao);
  glGenBuffers(1, &chunkData._vbo);
  glGenBuffers(1, &chunkData._ebo);

  glBindVertexArray(chunkData._vao);

  glBindBuffer(GL_ARRAY_BUFFER, chunkData._vbo);
  glBufferData(GL_ARRAY_BUFFER, ChunkData::ChunkVerticesSize, verticesData, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkData._ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ChunkData::ChunkIndicesSize, indicesData, GL_STATIC_DRAW);

  int stride = 5 * sizeof(GLfloat);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  _chunks[key] = chunkData;
  //_chunks.insert(std::make_pair(key, ChunkData(vertexArray, buffer)));

  delete verticesData;
  delete indicesData;

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

  glDeleteVertexArrays(1, &chunk->second._vao);
  glDeleteBuffers(1, &chunk->second._vbo);
  glDeleteBuffers(1, &chunk->second._ebo);

  _chunks.erase(chunk);

  return SUCCESS;
}

GLvoid* offsets[16] = {
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 0),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 1),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 2),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 3),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 4),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 5),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 6),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 7),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 8),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 9),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 10),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 11),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 12),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 13),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 14),
    (GLvoid*)(ChunkData::ChunkPartIndicesSize * 15),
};

void GlewRenderSystem::RenderChunks()
{
  _blocksShaderProgram->Set();

  _blockTextureAltlas->Set(GL_TEXTURE_2D);

  glm::mat4 view = _camera->GetView();
  glm::mat4 projection = _camera->GetProjection();
  glm::mat4 viewProjection = projection * view;
  _blocksShaderProgram->SetMat4("VP", viewProjection);

  for (const auto& chunk : _chunks)
  {
    const ChunkKey& chunkKey = chunk.first;
    const ChunkData& chunkData = chunk.second;

    glBindVertexArray(chunkData._vao);
    glMultiDrawElements(GL_TRIANGLES, chunkData.count, GL_UNSIGNED_INT, offsets, Chunk::PartsNumber);
  }
}
