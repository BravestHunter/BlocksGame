#pragma once

#include <crtdbg.h>

#include "unit_tests.hpp"

class CrtMemoryChecker
{
public:
  CrtMemoryChecker();
  ~CrtMemoryChecker();

private:
  _CrtMemState _initialState;
  _CrtMemState _finishState;
  _CrtMemState _diffState;
};
