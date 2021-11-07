#include "glew_block_shader_program.hpp"

#define BLOCK_VERTEX_SHADER "/block.vs"
#define BLOCK_GEOMETRY_SHADER "/block.gs"
#define BLOCK_FRAGMENT_SHADER "/block.fs"

#define BLOCK_VERTEX_SHADER_PATH SHADERS_DIRECTORY BLOCK_VERTEX_SHADER
#define BLOCK_GEOMETRY_SHADER_PATH SHADERS_DIRECTORY BLOCK_GEOMETRY_SHADER
#define BLOCK_FRAGMENT_SHADER_PATH SHADERS_DIRECTORY BLOCK_FRAGMENT_SHADER


GlewBlockShaderProgram::GlewBlockShaderProgram() : _vpUniformLocation(0)
{
  GlewShader* vertexShader = NULL;
  GlewShader* geometryShader = NULL;
  GlewShader* fragmentShader = NULL;

  int result = 0;
  result += (int)GlewShader::LoadFromFile(BLOCK_VERTEX_SHADER_PATH, GlewShaderType::Vertex, &vertexShader);
  result += (int)GlewShader::LoadFromFile(BLOCK_GEOMETRY_SHADER_PATH, GlewShaderType::Geometry, &geometryShader);
  result += (int)GlewShader::LoadFromFile(BLOCK_FRAGMENT_SHADER_PATH, GlewShaderType::Fragment, &fragmentShader);

  if (result > 0 ||
      vertexShader == NULL ||
      geometryShader == NULL ||
      fragmentShader == NULL)
  {
    // Something went wrong
    return;
  }

  if (result == 0 && 
      vertexShader != NULL &&
      geometryShader != NULL &&
      fragmentShader != NULL)
  {
    _shaderProgram = glCreateProgram();

    glAttachShader(_shaderProgram, vertexShader->GetId());
    glAttachShader(_shaderProgram, geometryShader->GetId());
    glAttachShader(_shaderProgram, fragmentShader->GetId());

    Link();

    if (_isLinked)
    {
      _vpUniformLocation = glGetUniformLocation(_shaderProgram, "VP");
    }
  }
}

GlewBlockShaderProgram::~GlewBlockShaderProgram()
{
}


void GlewBlockShaderProgram::SetViewProjection(const glm::mat4& mat)
{
  glUniformMatrix4fv(_vpUniformLocation, 1, GL_FALSE, &mat[0][0]);
}


OpResult GlewBlockShaderProgram::Create(GlewBlockShaderProgram** shaderProgram)
{
  return SUCCESS;
}
