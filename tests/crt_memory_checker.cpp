#include "crt_memory_checker.hpp"


CrtMemoryChecker::CrtMemoryChecker() : _initialState(), _finishState(), _diffState()
{
  _CrtMemCheckpoint(&_initialState);
}

CrtMemoryChecker::~CrtMemoryChecker()
{
  _CrtMemCheckpoint(&_finishState);

  bool isMemoryFreed = _CrtMemDifference(&_diffState, &_initialState, &_finishState) == 0;

  SECTION("Memory must be freed")
  {
    CHECK(isMemoryFreed);
  }
}
