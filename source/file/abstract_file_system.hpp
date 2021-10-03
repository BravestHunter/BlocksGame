#pragma once

#include "abstract_system.hpp"
#include "image.hpp"


/// <summary>
/// Represents api for working with OS's file system.
/// </summary>
class AbstractFileSystem : public AbstractSystem
{
public:
  AbstractFileSystem() = default;
  virtual ~AbstractFileSystem() override = default;

  virtual OpResult ReadFile(const char* path, char* buffer, int* size) = 0;
  virtual OpResult ReadImage(const char* path, Image& image) = 0;
};
