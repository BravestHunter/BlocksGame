#include "resource_system.hpp"

#include "stb_headers.hpp"
#include "freetype_headers.hpp"


#define CONTAINER_TEXTURE TEXTURES_DIRECTORY "/container.jpg"
#define DIRT_TEXTURE TEXTURES_DIRECTORY "/dirt.jpg"

#define ALLER_FONT "/aller/Aller_Rg.ttf"
#define ALLER_FONTPATH FONTS_DIRECTORY ALLER_FONT


ResourceSystem::ResourceSystem()
{

}

ResourceSystem::~ResourceSystem()
{

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


OpResult ResourceSystem::GetImage(const ResourceId id, Image& image)
{
  auto resourcePath = _recourcePaths.find(id);
  if (resourcePath == _recourcePaths.end())
  {
    return FAILURE;
  }

  std::vector<Byte> data;
  if (Container::GetFileSystem()->ReadBinary(DIRT_TEXTURE, data) == FAILURE)
  {
    return FAILURE;
  }

  /// TODO: remove this sad bytes copying...
  Byte* rawImageData = stbi_load_from_memory(&data[0], data.size(), &image.width, &image.height, &image.channels, 0);
  image.data = std::vector<Byte>(rawImageData, rawImageData + image.height * image.width * image.channels);
  delete rawImageData;

  return SUCCESS;
}

OpResult ResourceSystem::GetFont(const ResourceId id, AbstractFont** font)
{
  auto fontPath = _recourcePaths.find(id);
  if (fontPath == _recourcePaths.end())
  {
    return FAILURE;
  }

  // TODO: use file system to load fonts...
  FT_Face face;
  if (FT_New_Face(_freetypeLibrary, fontPath->second, 0, &face) != 0)
  {
    return FAILURE;
  }

  *font = new FreetypeFont(face);

  return SUCCESS;
}
