#pragma once

#include <cstddef>


/// <summary>
/// Represents universal resource identifier.
/// </summary>
struct ResourceId
{
public:
  ResourceId(const char* id);

  bool operator==(const ResourceId& other) const;

  std::size_t GetHashCode() const;

private:
  char _id[16];
};

class ResourceIdKeyHasher
{
public:
  std::size_t operator()(const ResourceId& key) const;
};
