#pragma once

#include "abstract_file_system.hpp"

/// <summary>
/// Represents FileSystem implemented using std.
/// </summary>
class CommonFileSystem : public AbstractFileSystem
{
public:
  CommonFileSystem();
  virtual ~CommonFileSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual OpResult ReadFile(const char* path, char* buffer, int* size) override;
  virtual OpResult ReadImage(const char* path, Image& image) override;
};
