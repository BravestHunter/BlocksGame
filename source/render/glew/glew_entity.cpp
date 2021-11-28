#include "glew_entity.hpp"


GlewEntity::GlewEntity() : _id(FreeId)
{
  // Nothing to do here
}

GlewEntity::~GlewEntity()
{
  // Nothing to do here
}


GLuint GlewEntity::GetId()
{
  return _id;
}
