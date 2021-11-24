#pragma once

#include "abstract_noise_2d.hpp"
#include "FastNoise/FastNoise.h"

class PerlinNoise2D : public AbstractNoise2D
{
public:
  PerlinNoise2D(int seed);
  virtual ~PerlinNoise2D() override;

  virtual float GetValue(float x, float y) override;
  virtual void GetValues(float* values, int startX, int startY, int lenX, int lenY) override;

private:
  int _seed;
  FastNoise::SmartNode<FastNoise::FractalFBm> _generator;
};
