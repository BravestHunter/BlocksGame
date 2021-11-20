#pragma once

#include <unordered_map>

#include "abstract_resource_system.hpp"
#include "container.hpp"
#include "freetype_font.hpp"


/// <summary>
/// Represents simple resource system.
/// Image loading uses stb library.
/// Font loading uses freetype library.
/// </summary>
class ResourceSystem : public AbstractResourceSystem
{
public:
  ResourceSystem();
  virtual ~ResourceSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual OpResult GetString(const ResourceId id, std::string& str) override;
  virtual OpResult GetImage(const ResourceId id, Image& image) override;
  virtual OpResult GetFont(const ResourceId id, AbstractFont** font) override;

private:
  std::unordered_map<ResourceId, const char*, ResourceIdKeyHasher> _recourcePaths {};
  FT_Library _freetypeLibrary = nullptr;
};
