#include "glew_texture.hpp"

#include <cassert>


GlewTexture::GlewTexture(Image& texture)
{
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  assert(texture.channels == 3);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, &texture.data[0]);

  glGenerateMipmap(GL_TEXTURE_2D);
}

GlewTexture::~GlewTexture()
{
  if (_id != GlewEntity::FreeId)
  {
    glDeleteTextures(1, &_id);
  }
}


void GlewTexture::Set(GLuint textureSpecifier)
{
  glActiveTexture(textureSpecifier);
  glBindTexture(GL_TEXTURE_2D, _id);
}
