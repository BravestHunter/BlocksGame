#include "glew_render_system.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "image.hpp"
#include "container.hpp"

#define DEFAULT_VERTEX_SHADER "/default.vs"
#define DEFAULT_FRAGMENT_SHADER "/default.fs"
#define DEFAULT_VERTEX_SHADER_PATH SHADERS_DIRECTORY DEFAULT_VERTEX_SHADER
#define DEFAULT_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY DEFAULT_FRAGMENT_SHADER
#define CONTAINER_TEXTURE TEXTURES_DIRECTORY "/container.jpg"
#define DIRT_TEXTURE TEXTURES_DIRECTORY "/dirt.jpg"


#include "model/map.hpp"


Map* _map = NULL;

unsigned int VBO, VAO;
unsigned int texture1;

unsigned int blocks_vbo, blocks_vao;
unsigned int grass_texture;


GlewRenderSystem::GlewRenderSystem() : _width(0), _height(0), _camera(NULL), _blocksShaderProgram(NULL)
{
  _camera = new Camera();

  _map = new Map();

  for (int i = 0; i < Chunk::BlocksNumber; i++)
  {
    _map->chunk.blocks[i] = 1;
  }
}

GlewRenderSystem::~GlewRenderSystem()
{
  delete _camera;

  delete _map;
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

  //================================
  unsigned int vertices[Chunk::BlocksNumber];
  std::copy(std::begin(_map->chunk.blocks), std::end(_map->chunk.blocks), std::begin(vertices));

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  size_t stride = sizeof(unsigned int);

  glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glVertexAttribDivisor(0, 1);



  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
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
  float blocks[Chunk::BlocksNumber];
  for (int i = 0; i < Chunk::Width; i++)
  {
    for (int j = 0; j < Chunk::Length; j++)
    {
      for (int k = 0; k < Chunk::Height; k++)
      {
        blocks[i * Chunk::Length * Chunk::Height + j * Chunk::Height + k] = rand() % 2;
      }
    }
  }

  glGenVertexArrays(1, &blocks_vao);
  glGenBuffers(1, &blocks_vbo);

  glBindVertexArray(blocks_vao);

  glBindBuffer(GL_ARRAY_BUFFER, blocks_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

  delete _blocksShaderProgram;

  //================================
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  //================================

  _isInitialized = false;
  return SUCCESS;
}


void GlewRenderSystem::Render()
{
  glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _blocksShaderProgram->Set();

  glm::mat4 projection = glm::perspective(glm::radians(_camera->GetZoom()), (float)_width / (float)_height, 0.1f, 100.0f);
  glm::mat4 view = _camera->GetViewMatrix();
  glm::mat4 viewProjection = projection * view;

  _blocksShaderProgram->SetViewProjection(viewProjection);

  // Draw
  glBindVertexArray(VAO);
  glDrawArrays(GL_POINTS, 0, Chunk::BlocksNumber);
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
