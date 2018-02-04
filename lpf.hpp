#pragma once
#include "sink.hpp"

// Low-pass filter
class Lpf: public Sink
{
public:
  Lpf(Sink *sink, float k);
  void queue(int16_t *buff, size_t) override;

private:
  Sink *sink;
  float a = 0;
  float k;
};
