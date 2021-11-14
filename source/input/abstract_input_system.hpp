#pragma once

#include "abstract_system.hpp"
#include "keyboard_key_state.hpp"
#include "keyboard_key.hpp"


class AbstractInputSystem : public AbstractSystem
{
public:
  virtual void ProcessEvents() = 0;

  virtual KeyboardKeyState GetKeyStatus(KeyboardKey key) const = 0;

  virtual float GetMouseDeltaX() = 0;
  virtual float GetMouseDeltaY() = 0;
  virtual void ClearMouseDelta() = 0;
};
