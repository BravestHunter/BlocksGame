#include "common_file_system.hpp"

#include <fstream>
#include <sstream>

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


OpResult CommonFileSystem::ReadText(const char* path, std::string& text)
{
  std::ifstream inputStream;

  try
  {
    inputStream.open(path);
    if (!inputStream.is_open())
    {
      return FAILURE;
    }

    std::stringstream stringStream;
    stringStream << inputStream.rdbuf();
    inputStream.close();

    text = stringStream.str();
  }
  catch (std::ifstream::failure& e)
  {
    inputStream.close();

    return FAILURE;
  }

  return SUCCESS;
}

OpResult CommonFileSystem::ReadBinary(const char* path, DataBuffer<Byte>& buffer)
{
  std::ifstream inputStream;

  try
  {
    inputStream.open(path, std::ios::in | std::ios::binary);
    if (!inputStream.is_open())
    {
      inputStream.close();
      return FAILURE;
    }

    inputStream.seekg(0, std::ios::end);
    std::streampos size = inputStream.tellg();
    Byte* bytes = new Byte[size];
    inputStream.seekg(0, std::ios::beg);
    inputStream.read((char*)bytes, size);
    buffer = DataBuffer<Byte>(bytes, size);
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
