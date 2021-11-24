#include "perlin_noise_2d.hpp"

#include <iostream>


PerlinNoise2D::PerlinNoise2D(int seed) : _seed(seed)
{
  auto noise = FastNoise::New<FastNoise::Perlin>();

  _generator = FastNoise::New<FastNoise::FractalFBm>();
  _generator->SetSource(noise);
  _generator->SetOctaveCount(5);
}

PerlinNoise2D::~PerlinNoise2D()
{
  // Nothing to do here
}


float PerlinNoise2D::GetValue(float x, float y)
{
  return _generator->GenSingle2D(x, y, _seed);
}

void PerlinNoise2D::GetValues(float* values, int startX, int startY, int lenX, int lenY)
{
  _generator->GenUniformGrid2D(values, startX, startY, lenX, lenY, 0.005, _seed);
}