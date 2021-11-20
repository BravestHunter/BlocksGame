#pragma once

#include <vector>

#include "types.hpp"


struct Image
{
  std::vector<Byte> data {};
  int size = 0;
  int width = 0;
  int height = 0;
  int channels = 0;
};
