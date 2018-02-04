#pragma once
#include "sink.hpp"
#include <vector>

// Mixer
class Mix
{
public:
  class Input : public Sink
  {
    friend Mix;
  public:
    Input(Mix *);
    void queue(int16_t *buff, size_t) override;

  private:
    Mix *mix;
    std::vector<int16_t> buff;
  };
  Mix(Sink *, int inputNum);
  Input *getInput(int);

private:
  std::vector<Input> inputs;
  Sink *sink;
  void process();
};
