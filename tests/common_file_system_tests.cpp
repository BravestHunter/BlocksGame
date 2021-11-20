#include "unit_tests.hpp"
#include "crt_memory_checker.hpp"

#include "file/abstract_file_system.hpp"
#include "file/common_file_system.hpp"


TEST_CASE("Common file system initialization test") 
{
  CommonFileSystem fileSystem;
  fileSystem.Init();
  
  REQUIRE(fileSystem.IsInitialized());
  
  fileSystem.Deinit();
}

TEST_CASE("Common file system read empty text file test")
{
  CommonFileSystem fileSystem;
  fileSystem.Init();

  std::string text;
  fileSystem.ReadString(TEST_RESOURCE_DIRECTORY "/empty_file.txt", text);

  SECTION("File text should be empty")
  {
    REQUIRE(text == "");
  }

  fileSystem.Deinit();
}

TEST_CASE("Common file system read simple text file test")
{
  CommonFileSystem fileSystem;
  fileSystem.Init();

  std::string text;
  fileSystem.ReadString(TEST_RESOURCE_DIRECTORY "/simple_text_file.txt", text);

  SECTION("File text should be equal to expected")
  {
    REQUIRE(text == "Hello, Mr. Notch!");
  }

  fileSystem.Deinit();
}

TEST_CASE("Common file system read empty binary file test")
{
  CommonFileSystem fileSystem;
  fileSystem.Init();

  std::vector<Byte> buffer;
  fileSystem.ReadBinary(TEST_RESOURCE_DIRECTORY "/empty_file.txt", buffer);

  SECTION("File data should be empty")
  {
    REQUIRE(buffer.size() == 0);
  }

  fileSystem.Deinit();
}

TEST_CASE("Common file system read simple binary file test")
{
  CommonFileSystem fileSystem;
  fileSystem.Init();

  std::vector<Byte> buffer;
  fileSystem.ReadBinary(TEST_RESOURCE_DIRECTORY "/simple_text_file.txt", buffer);

  SECTION("File data should be equal to expected")
  {
    char expectedData[] = "Hello, Mr. Notch!";
    size_t expectedSize = sizeof(expectedData) - 1; // Skip null-termiantor

    for (int i = 0; i < expectedSize; i++)
    {
      REQUIRE(buffer[i] == expectedData[i]);
    }
    REQUIRE(buffer.size() == expectedSize);
  }

  fileSystem.Deinit();
}

TEST_CASE("Common file system cleanup test")
{
  CrtMemoryChecker memoryChecker;

  AbstractFileSystem* fileSystem = new CommonFileSystem();
  fileSystem->Init();

  fileSystem->Deinit();
  delete fileSystem;
}
