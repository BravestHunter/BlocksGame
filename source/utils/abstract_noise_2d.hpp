#pragma once


class AbstractNoise2D
{
public:
  virtual ~AbstractNoise2D() {};

  virtual float GetValue(float x, float y) = 0;
  virtual void GetValues(float* values, int startX, int startY, int lenX, int lenY) = 0;
};
