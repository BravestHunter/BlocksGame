#include "container.hpp"

#include <exception>


void Container::SetFileSystem(AbstractFileSystem* fileSystem)
{
  _fileSystem = fileSystem;
}


AbstractFileSystem* Container::GetFileSystem()
{
  return _fileSystem;
}


bool Container::IsReady()
{
	return 
		_fileSystem != nullptr && _fileSystem->IsInitialized();
}

void Container::CleanUp()
{
  delete _fileSystem;
}


AbstractFileSystem* Container::_fileSystem = nullptr;


ContainerCleanup::~ContainerCleanup()
{
  Container::CleanUp();
}
