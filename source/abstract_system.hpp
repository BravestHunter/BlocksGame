#pragma once

#include "op_result.hpp"


/// <summary>
/// Represents some kind of game system.
/// Each systems is responsable for it's part of fuctionality.
/// One system instance allowed. (And there is no protection for creating more, so be careful.)
/// </summary>
class AbstractSystem
{
public:
  AbstractSystem() = default;
  virtual ~AbstractSystem() = default;

  virtual OpResult Init() = 0;
  virtual OpResult Deinit() = 0;
  bool IsInitialized();

protected:
  bool _isInitialized = false;
};
