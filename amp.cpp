#include "amp.hpp"

Amp::Amp(Sink *sink, float k) : sink(sink), k(k)
{
}

void Amp::queue(int16_t *b, size_t size)
{
  for (auto iter = b; iter != b + size; ++iter)
    *iter *= k;
  sink->queue(b, size);
}
