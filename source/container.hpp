#pragma once

#include "file/abstract_file_system.hpp"


class Container
{
public:
  static void SetFileSystem(AbstractFileSystem* fileSystem);

  static AbstractFileSystem* GetFileSystem();

  static bool IsReady();
  static void CleanUp();

private:
  static AbstractFileSystem* _fileSystem;
};

class ContainerCleanup
{
public:
  ContainerCleanup() = default;
  ~ContainerCleanup();
};
