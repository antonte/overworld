#pragma once

class Synth
{
public:
  virtual void setTempo(int) = 0;
  virtual void play(int note, int duration) = 0;
  virtual void pause(int duration) = 0;
};
