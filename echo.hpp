#pragma once
#include "sink.hpp"
#include <vector>

// Echo filter
// Adds echo to the signal
class Echo : public Sink
{
public:
  Echo(Sink *sink, int delay, float decay);
  void queue(int16_t *buff, size_t) override;

private:
  Sink *sink;
  float decay;
  std::vector<int16_t> buff;
  int p = 0;
};
