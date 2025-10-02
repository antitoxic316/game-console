#pragma once

#include <Program.h>

class IDispatchable
{
public:
  IDispatchable() = default;
  virtual ~IDispatchable() = default;

  virtual Program *getProgramPtr() = 0;
  virtual void init() = 0;
};