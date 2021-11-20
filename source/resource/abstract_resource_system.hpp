#pragma once

#include "abstract_system.hpp"
#include "resource_id.hpp"
#include "image.hpp"
#include "abstract_font.hpp"


/// <summary>
/// Represents game resources provider.
/// </summary>
class AbstractResourceSystem : public AbstractSystem
{
public:
  virtual OpResult GetString(const ResourceId id, std::string& str) = 0;
  virtual OpResult GetImage(const ResourceId id, Image& image) = 0;
  virtual OpResult GetFont(const ResourceId id, AbstractFont** font) = 0;
};
