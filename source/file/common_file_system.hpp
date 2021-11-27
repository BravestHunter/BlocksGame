#pragma once

#include "abstract_file_system.hpp"
#include "container.hpp"


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

  virtual OpResult ReadString(const char* path, std::string& str) override;
  virtual OpResult ReadBinary(const char* path, std::vector<Byte>& buffer) override;
};
