#pragma once
#include "sdlpp.hpp"
#include "sink.hpp"

class Audio : public Sink
{
public:
  Audio();
  virtual void queue(int16_t *buff, size_t);

private:
  sdl::Audio audio;
};
