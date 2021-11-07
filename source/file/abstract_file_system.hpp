#pragma once

#include <string>

#include "abstract_system.hpp"
#include "data_buffer.hpp"
#include "types.hpp"
#include "image.hpp"


/// <summary>
/// Represents api for working with OS's file system.
/// </summary>
class AbstractFileSystem : public AbstractSystem
{
public:
  AbstractFileSystem() = default;
  virtual ~AbstractFileSystem() override = default;

  virtual OpResult ReadText(const char* path, std::string& text) = 0;
  virtual OpResult ReadBinary(const char* path, DataBuffer<Byte>& buffer) = 0;
  virtual OpResult ReadImage(const char* path, Image& image) = 0;
};
