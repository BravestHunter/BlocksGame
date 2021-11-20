#include "resource_id.hpp"

#include <string>


ResourceId::ResourceId(const char* id)
{
  strcpy(_id, id);
}


bool ResourceId::operator==(const ResourceId& other) const
{
  return strcmp(_id, other._id) == 0;
}


std::size_t ResourceId::GetHashCode() const
{
  size_t result = 0;
  const size_t prime = 31;

  for (size_t i = 0, size = strlen(_id); i < size; i++)
  {
    result = _id[i] + (result * prime);
  }

  return result;
}


std::size_t ResourceIdKeyHasher::operator()(const ResourceId& key) const
{
  return key.GetHashCode();
}
