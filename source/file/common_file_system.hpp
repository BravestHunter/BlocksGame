#pragma once

#include "abstract_file_system.hpp"


/// <summary>
/// Represents universal FileSystem implemented with help of std.
/// </summary>
class CommonFileSystem : public AbstractFileSystem
{
public:
  CommonFileSystem();
  virtual ~CommonFileSystem() override;

  virtual OpResult Init() override;
  virtual OpResult Deinit() override;

  virtual OpResult ReadText(const char* path, std::string& text) override;
  virtual OpResult ReadBinary(const char* path, std::vector<Byte>& buffer) override;
};
