#include "resource_system.hpp"

#include "stb_headers.hpp"
#include "freetype_headers.hpp"


#define CONTAINER_TEXTURE TEXTURES_DIRECTORY "/container.jpg"
#define DIRT_TEXTURE TEXTURES_DIRECTORY "/dirt.jpg"

#define ALLER_FONT "/aller/Aller_Rg.ttf"
#define ALLER_FONTPATH FONTS_DIRECTORY ALLER_FONT


ResourceSystem::ResourceSystem()
{
  // Nothing to do here
}

ResourceSystem::~ResourceSystem()
{
  // Nothing to do here
}


OpResult ResourceSystem::Init()
{
  // TODO: load resource paths data from some resources-config file
  _recourcePaths["Tex_Dirt"] = DIRT_TEXTURE;
  _recourcePaths["Font_Aller"] = ALLER_FONTPATH;

  // Initialize freetype library
  if (FT_Init_FreeType(&_freetypeLibrary))
  {
    return FAILURE;
  }

  _isInitialized = true;

  return SUCCESS;
}

OpResult ResourceSystem::Deinit()
{
  // Clear resource dictionary
  _recourcePaths.clear();

  // Free freetype library
  FT_Done_FreeType(_freetypeLibrary);

  _isInitialized = false;

  return SUCCESS;
}


OpResult ResourceSystem::GetString(const ResourceId id, std::string& str)
{
  auto resource = _recourcePaths.find(id);
  if (resource == _recourcePaths.end())
  {
    return FAILURE;
  }

  return Container::GetFileSystem()->ReadString(resource->second, str);
}

OpResult ResourceSystem::GetImage(const ResourceId id, Image& image)
{
  auto resource = _recourcePaths.find(id);
  if (resource == _recourcePaths.end())
  {
    return FAILURE;
  }

  std::vector<Byte> data;
  if (Container::GetFileSystem()->ReadBinary(resource->second, data) == FAILURE)
  {
    return FAILURE;
  }

  /// TODO: remove this sad bytes copying...
  Byte* rawData = stbi_load_from_memory(&data[0], data.size(), &image.width, &image.height, &image.channels, 0);
  image.data = std::vector<Byte>(rawData, rawData + image.height * image.width * image.channels);
  delete rawData;

  return SUCCESS;
}

OpResult ResourceSystem::GetFont(const ResourceId id, AbstractFont** font)
{
  auto resource = _recourcePaths.find(id);
  if (resource == _recourcePaths.end())
  {
    return FAILURE;
  }

  std::vector<Byte> data;
  if (Container::GetFileSystem()->ReadBinary(resource->second, data) == FAILURE)
  {
    return FAILURE;
  }

  /// TODO: remove this sad bytes copying...
  Byte* rawData = new Byte[data.size()];
  std::memcpy(rawData, &data[0], data.size());

  FT_Face face;
  if (FT_New_Memory_Face(_freetypeLibrary, rawData, data.size(), 0, &face) != 0)
  {
    return FAILURE;
  }

  *font = new FreetypeFont(face, rawData);

  return SUCCESS;
}
