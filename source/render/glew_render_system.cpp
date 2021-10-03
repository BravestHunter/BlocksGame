#include "glew_render_system.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "image.hpp"
#include "container.hpp"

#define DEFAULT_VERTEX_SHADER "/default.vs"
#define DEFAULT_FRAGMENT_SHADER "/default.fs"
#define DEFAULT_VERTEX_SHADER_PATH SHADERS_DIRECTORY DEFAULT_VERTEX_SHADER
#define DEFAULT_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY DEFAULT_FRAGMENT_SHADER
#define CONTAINER_TEXTURE TEXTURES_DIRECTORY "/container.jpg"


unsigned int VBO, VAO;
unsigned int texture1;


GlewRenderSystem::GlewRenderSystem()
{
  _camera = new Camera();
}

GlewRenderSystem::~GlewRenderSystem()
{
  delete _camera;
  delete _shader;
}


OpResult GlewRenderSystem::Init()
{
  if (_isInitialized)
  {
    return FAILURE;
  }

  AbstractFileSystem* fileSystem = Container::GetFileSystem();

  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_DEPTH_TEST);

  //================================
  _shader = new Shader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);

  float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  Image texture;
  OpResult result = fileSystem->ReadImage(CONTAINER_TEXTURE, texture);
  if (result == SUCCESS)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }

  _shader->Use();
  _shader->SetInt("texture1", 0);
  //================================

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
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  //================================

  _isInitialized = false;
  return SUCCESS;
}


void GlewRenderSystem::RenderScene()
{
  glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);

  _shader->Use();

  glm::mat4 projection = glm::perspective(glm::radians(_camera->GetZoom()), (float)_width / (float)_height, 0.1f, 100.0f);
  _shader->SetMat4("projection", projection);

  glm::mat4 view = _camera->GetViewMatrix();
  _shader->SetMat4("view", view);

  glBindVertexArray(VAO);
  for (unsigned int i = 0; i < 10; i++)
  {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(i, 0, 0));
    _shader->SetMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
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
