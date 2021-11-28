#include "glew_vertex_array.hpp"


GlewVertexArray::GlewVertexArray()
{
  glGenVertexArrays(1, &_id);
}

GlewVertexArray::~GlewVertexArray()
{
  if (_id != GlewEntity::FreeId)
    glDeleteVertexArrays(1, &_id);
}


void GlewVertexArray::Bind() const
{
  glBindVertexArray(_id);
}
