#pragma once
#include <cstdint>
#include <cstddef>

class Sink
{
public:
  virtual void queue(int16_t *buff, size_t) = 0;
};
