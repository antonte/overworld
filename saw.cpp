#include "saw.hpp"

#include "const.hpp"
#include <cmath>

Saw::Saw(Sink *sink) : sink(sink)
{
}

void Saw::setTempo(int value)
{
  tempo = value;
}

void Saw::play(int note, int duration)
{
  int freq = 440 * pow(2, (note + 3 - 12) / 12.0) * 0xffff / sampleRate;
  for (int i = 0; i < duration * 60 * sampleRate / tempo / quarter - 480; ++i)
    addSample(sum += freq);
  for (int i = 0; i < 480; ++i)
    addSample(0);
}

void Saw::pause(int duration)
{
  for (int i = 0; i < duration * 60 * sampleRate / 132 / 32; ++i)
    addSample(0);
}

void Saw::addSample(int16_t sample)
{
  buff[idx] = sample / 4;
  ++idx;
  if (idx >= buffSize)
  {
    sink->queue(buff, idx);
    idx = 0;
  }
}
