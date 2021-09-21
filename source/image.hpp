#pragma once

struct Image
{
  ~Image()
  {
    delete data;
  }

  unsigned char* data;
  int size;
  int width;
  int height;
  int channels;
};
