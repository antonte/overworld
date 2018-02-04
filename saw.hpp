#pragma once
#include "sink.hpp"
#include "synth.hpp"
#include "const.hpp"

// Saw synth
class Saw : public Synth
{
public:
  Saw(Sink *);
  void setTempo(int) override;
  void play(int note, int duration) override;
  void pause(int duration) override;

private:
  Sink *sink;
  int tempo = 120;
  int sum = 0;
  int16_t buff[buffSize];
  int idx = 0;
  void addSample(int16_t sample);
};
