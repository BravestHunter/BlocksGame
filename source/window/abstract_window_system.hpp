#pragma once

#include "abstract_system.hpp"


class AbstractWindowSystem : public AbstractSystem
{
public:
  virtual void SwapBuffers() = 0;
  virtual void RequestClose() = 0;

  virtual bool IsCloseRequested() const = 0;
  virtual unsigned int GetWidth() = 0;
  virtual unsigned int GetHeight() = 0;
};
