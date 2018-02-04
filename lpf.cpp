#include "lpf.hpp"

Lpf::Lpf(Sink *sink, float k) : sink(sink), k(k)
{
}

void Lpf::queue(int16_t *b, size_t size)
{
  for (auto iter = b; iter != b + size; ++iter)
  {
    a = k * (a - *iter) + *iter;
    *iter = a;
  }
  sink->queue(b, size);
}
