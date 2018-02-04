#include "echo.hpp"

Echo::Echo(Sink *sink, int delay, float decay) : sink(sink), decay(decay), buff(delay)
{
}

void Echo::queue(int16_t *b, size_t size)
{
  std::vector<int16_t> tmp;
  for (auto iter = b; iter != b + size; ++iter)
  {
    auto a = buff[p] + *iter;
    tmp.push_back(a);
    buff[p] = a * decay;
    ++p;
    if (p >= static_cast<int>(buff.size()))
      p = 0;
  }
  sink->queue(tmp.data(), tmp.size());
}
