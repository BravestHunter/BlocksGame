#include "common_file_system.hpp"

#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


CommonFileSystem::CommonFileSystem()
{
  // Nothing to do here
}

CommonFileSystem::~CommonFileSystem()
{
  // Nothing to do here
}


OpResult CommonFileSystem::Init()
{
  _isInitialized = true;
  return SUCCESS;
}

OpResult CommonFileSystem::Deinit()
{
  _isInitialized = false;
  return SUCCESS;
}


OpResult CommonFileSystem::ReadFile(const char* path, char* buffer, int* size)
{
  std::ifstream inputStream;

  try
  {
    inputStream.open(path);
    if (!inputStream.is_open())
    {
      return FAILURE;
    }

    std::streampos size = inputStream.tellg();
    buffer = new char[size];
    inputStream.seekg(0, std::ios::beg);
    inputStream.read(buffer, size);
  }
  catch (std::ifstream::failure& e)
  {
    inputStream.close();

    return FAILURE;
  }
  inputStream.close();

  return SUCCESS;
}

OpResult CommonFileSystem::ReadImage(const char* path, Image& image)
{
  stbi_set_flip_vertically_on_load(true);
  
  image.data = stbi_load(path, &image.width, &image.height, &image.channels, 0);
  if (!image.data)
  {
    return FAILURE;
  }

  return SUCCESS;
}
