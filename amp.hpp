#pragma once
#include "sink.hpp"

// Amplifies the signal with coefficient k
class Amp : public Sink
{
public:
  Amp(Sink *sink, float k);
  void queue(int16_t *buff, size_t) override;

private:
  Sink *sink;
  float k;
};
