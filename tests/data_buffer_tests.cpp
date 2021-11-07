#include "unit_tests.hpp"
#include "crt_memory_checker.hpp"

#include "data_buffer.hpp"


TEST_CASE("Data buffer data access test")
{
  int size = 4;
  char* data = new char[size] { -1, 0, 1, 2 };
  DataBuffer<char> buffer(data, size);

  int givenSize = buffer.GetSize();
  char* givenData = buffer.GetData();

  SECTION("Data should be equal to initial one")
  {
    REQUIRE(givenSize == size);

    for (int i = 0; i < size; i++)
    {
      REQUIRE(givenData[i] == data[i]);
    }
  }
}

TEST_CASE("Data buffer cleanup test")
{
  CrtMemoryChecker memoryChecker;

  int size = 4;
  char* data = new char[size];
  DataBuffer<char>* buffer = new DataBuffer<char>(data, size);

  delete buffer;
}
