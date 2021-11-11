#include "glew_render_system.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "image.hpp"
#include "container.hpp"

#define DEFAULT_VERTEX_SHADER "/default.vs"
#define DEFAULT_FRAGMENT_SHADER "/default.fs"
#define GLYPH_VERTEX_SHADER "/glyph.vs"
#define GLYPH_FRAGMENT_SHADER "/glyph.fs"

#define DEFAULT_VERTEX_SHADER_PATH SHADERS_DIRECTORY DEFAULT_VERTEX_SHADER
#define DEFAULT_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY DEFAULT_FRAGMENT_SHADER
#define GLYPH_VERTEX_SHADER_PATH SHADERS_DIRECTORY GLYPH_VERTEX_SHADER
#define GLYPH_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY GLYPH_FRAGMENT_SHADER

#define DEFAULT_FONTS_PATH RESOURCE_DIRECTORY "/fonts"
#define QUICKSAND_FONT "/alter/Aller_Rg.ttf"
#define QUICKSAND_FONTPATH DEFAULT_FONTS_PATH QUICKSAND_FONT

#define CONTAINER_TEXTURE TEXTURES_DIRECTORY "/container.jpg"
#define DIRT_TEXTURE TEXTURES_DIRECTORY "/dirt.jpg"


GlewRenderSystem::GlewRenderSystem() : _width(0), _height(0), _camera(NULL), _blocksShaderProgram(NULL)
{
  _camera = new Camera();

  _chunk = new Chunk();

  for (int i = 0; i < Chunk::PartsNumber; i++)
  {
    ChunkPart& part = _chunk->parts[i];
    
    for (int j = 0; j < ChunkPart::BlocksNumber; j++)
    {
      part.blocks[j] = rand() % 4 > 0 ? 0 : 1;
    }
  }
}

GlewRenderSystem::~GlewRenderSystem()
{
  delete _chunk;

  delete _camera;

  glDeleteTextures(1, &_blockTexture);

  for (auto c = _characters.begin(); c != _characters.end(); c++)
  {
    glDeleteTextures(1, &c->second.TextureID);
  }

  delete _blocksShaderProgram;
  delete _glyphShaderProgram;
}


OpResult GlewRenderSystem::Init()
{
  if (_isInitialized)
  {
    // Double initialize is not allowed
    return FAILURE;
  }

  AbstractFileSystem* fileSystem = Container::GetFileSystem();

  glewExperimental = GL_TRUE;
  glewInit();

  _blocksShaderProgram = new GlewBlockShaderProgram();
  if (!_blocksShaderProgram->IsLinked())
  {
    return FAILURE;
  }

  std::string source;
  fileSystem->ReadText(GLYPH_VERTEX_SHADER_PATH, source);
  GlewShader glyphVertexShader(source.c_str(), GlewShaderType::Vertex);
  fileSystem->ReadText(GLYPH_FRAGMENT_SHADER_PATH, source);
  GlewShader glyphFragmentShader(source.c_str(), GlewShaderType::Fragment);
  _glyphShaderProgram = new GlewShaderProgram(glyphVertexShader, glyphFragmentShader);
  if (!_glyphShaderProgram->IsLinked())
  {
    return FAILURE;
  }

  //================================
  unsigned unsigned int vertices[Chunk::BlocksNumber];
  //std::copy(std::begin(_chunk->parts), std::end(_chunk->parts), std::begin(vertices));
  std::memcpy(&vertices, &_chunk->parts, sizeof(Block) * Chunk::BlocksNumber);

  glGenVertexArrays(1, &_blocksVAO);
  glGenBuffers(1, &_blocksVBO);

  glBindVertexArray(_blocksVAO);

  glBindBuffer(GL_ARRAY_BUFFER, _blocksVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  size_t stride = sizeof(unsigned int);

  glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  //glVertexAttribDivisor(0, 1);



  glGenTextures(1, &_blockTexture);
  glBindTexture(GL_TEXTURE_2D, _blockTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  Image texture;
  OpResult result = fileSystem->ReadImage(DIRT_TEXTURE, texture);
  if (result == SUCCESS)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }

  //================================

  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
    return FAILURE;
  }
  FT_Face face;
  if (FT_New_Face(ft, QUICKSAND_FONTPATH, 0, &face))
  {
    return FAILURE;
  }

  FT_Set_Pixel_Sizes(face, 0, 32);

  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
  {
    return FAILURE;
  }


  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
    };
    _characters.insert(std::pair<GLchar, Character>(c, character));
  }


  glGenVertexArrays(1, &_glyphVAO);
  glGenBuffers(1, &_glyphVBO);
  glBindVertexArray(_glyphVAO);
  glBindBuffer(GL_ARRAY_BUFFER, _glyphVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  FT_Done_Face(face);   // ���������� ������ � ������� face
  FT_Done_FreeType(ft); // ���������� ������ FreeType

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

  //================================
  glDeleteVertexArrays(1, &_blocksVAO);
  glDeleteBuffers(1, &_blocksVBO);
  //================================
  glDeleteVertexArrays(1, &_glyphVAO);
  glDeleteBuffers(1, &_glyphVBO);
  //================================

  _isInitialized = false;
  return SUCCESS;
}


void GlewRenderSystem::Render()
{
  glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _blocksShaderProgram->Set();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _blockTexture);

  glm::mat4 projection = glm::perspective(glm::radians(_camera->GetZoom()), (float)_width / (float)_height, 0.1f, 100.0f);
  glm::mat4 view = _camera->GetViewMatrix();
  glm::mat4 viewProjection = projection * view;

  _blocksShaderProgram->SetViewProjection(viewProjection);

  // Draw
  glBindVertexArray(_blocksVAO);
  glDrawArrays(GL_POINTS, 0, Chunk::BlocksNumber);
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
    Character ch = _characters[*c];

    GLfloat xpos = x + ch.Bearing.x * scale;
    //GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
    GLfloat ypos = y + (ch.Size.y - ch.Bearing.y) * scale;

    GLfloat w = ch.Size.x * scale;
    GLfloat h = ch.Size.y * scale;
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
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, _glyphVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

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
