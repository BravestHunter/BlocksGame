#include "glew_buffer.hpp"


GlewBuffer::GlewBuffer() : _size(0), _type(0), _usage(0)
{
  // Nothing to do here
}

GlewBuffer::GlewBuffer(const void* data, size_t size, GLuint type, GLenum usage) : _size(size), _type(type), _usage(usage)
{
  glGenBuffers(1, &_id);

  glBindBuffer(type, _id);
  glBufferData(type, size, data, usage);
  glBindBuffer(type, 0);
}

GlewBuffer::~GlewBuffer()
{
  if (_id != GlewEntity::FreeId)
    glDeleteBuffers(1, &_id);
}


void GlewBuffer::Bind() const
{
  glBindBuffer(_type, _id);
}
