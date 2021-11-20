#include "common_file_system.hpp"

#include <fstream>
#include <sstream>

#include <vector>


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

    text = stringStream.str();
  }
  catch (std::ifstream::failure& e)
  {
    return FAILURE;
  }

  return SUCCESS;
}

OpResult CommonFileSystem::ReadBinary(const char* path, std::vector<Byte>& buffer)
{
  std::ifstream inputStream;

  try
  {
    inputStream.open(path, std::ios::in | std::ios::binary);
    if (!inputStream.is_open())
    {
      return FAILURE;
    }

    inputStream.seekg(0, std::ios::end);
    std::streampos size = inputStream.tellg();
    if (size == 0)
    {
      return SUCCESS;
    }

    buffer = std::vector<Byte>(size);
    inputStream.seekg(0, std::ios::beg);
    inputStream.read((char*)(&buffer[0]), size);
  }
  catch (std::ifstream::failure& e)
  {
    return FAILURE;
  }

  return SUCCESS;
}
