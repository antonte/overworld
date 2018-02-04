#include "sdlpp.hpp"
#include <iostream>

const int quarter = 32;
const int tempo = 132;
const int sampleRate = 48000;
const int buffSize = 4096;

SDL_AudioSpec obtained;

sdl::Init init(SDL_INIT_AUDIO);

SDL_AudioSpec *desired()
{
  static SDL_AudioSpec spec;
  SDL_memset(&spec, 0, sizeof(spec));
  spec.freq = sampleRate;
  spec.format = AUDIO_S16;
  spec.channels = 1;
  spec.samples = buffSize;
  spec.callback = nullptr;
  return &spec;
}

sdl::Audio audio(nullptr, false, desired(), &obtained, 0);

int note = 0;
int duration = quarter;

void addSample(int16_t sample)
{
  static int16_t buff[buffSize];
  static int idx = 0;
  buff[idx] = sample;
  ++idx;
  if (idx >= buffSize)
  {
    audio.queue(buff, idx * sizeof(int16_t));
    idx = 0;
  }
}

void play()
{
  int freq = 220 * pow(2, (note + 3) / 12.0) * 0xffff / sampleRate;
  static int16_t sum = 0;
  for (int i = 0; i < duration * 60 * sampleRate / tempo / quarter - 480; ++i)
    addSample(sum += freq);
  for (int i = 0; i < 480; ++i)
    addSample(0);
}

void key(int n)
{
  note = n;
  duration = 32;
}

void n(int n = 0, int num = 1, int den = 1)
{
  note += n;
  duration = duration * num / den;
  play();
}

void pause()
{
  for (int i = 0; i < duration * 60 * sampleRate / 132 / 32; ++i)
    addSample(0);
}

void p(int num = 1, int den = 1)
{
  duration = duration * num / den;
  pause();
}

int main(int, char **)
{
  audio.pause(false);
  auto l1 = []() { n(-4, 3, 4), n(-5, 1, 3); };
  // bar 1
  key(5);
  n(9), l1(), n(-1, 2), n(1, 1, 2), n(2, 5);

  for (int i = 0; i < 2; ++i)
  {
    // bar 2
    key(5);
    auto l3 = []() {
      auto l2 = []() { n(0, 1, 2), n(); };
      l2(), n(0, 2), l2();
    };
    n(4, 1, 2), l3(), n(1, 2), l3(), n(-1, 2), l3(), n(1, 2), n(0, 3);

    // bar 4
    key(5);
    auto l4 = [&l1]() { l1(), n(2), n(3, 2), n(0, 3, 2), p(1, 3); };
    auto l5 = []() { n(-2, 2), n(5); };
    auto l6 = [&l5]() { l5(), n(), n(7), n(-3, 3, 2), n(-2, 5, 3); };
    auto l7 = [&l5]() { l5(), n(5, 1, 2), n(-1), n(-2), n(-2), n(0, 8); };
    n(4), l4(), n(-3), l6();
    key(5);
    n(4), l4(), n(-3), l7();

    // bar 8
    key(5);
    n(4), l4(), n(-3), l6(), n(2, 4, 5), l4(), n(-3), l7();

    // bar 12
    key(5);
    auto l8 = []() { n(-4), n(-5, 2, 3), n(9, 3, 2), n(-4, 5, 3); };
    auto l9 = []() { n(-3), n(-5, 2); };
    n(4, 3, 4), l8(), n(3, 1, 5), l9(), n(8, 3, 2), n(-1, 9, 3), n(2, 3, 9), l8(), n(3, 1, 5), l9(),
      n(12, 6);

    // bar 16
    key(5);
    n(4), l4(), n(2), n(2), n(-4), n(-5, 2), n(2, 3, 2), n(3, 8, 3), n(-3, 1, 8), n(10, 2), n(2),
      n(-2), n(2), n(-2, 2), n(-2, 1, 4), n(-1), n(-2, 2), n(-2, 4), p();

    // bar 20
    key(5);
    auto l10 = []() { n(-3, 2), n(3, 3, 2), n(2, 2, 3); };
    n(0, 1, 4), l10(), n(2, 1, 2), n(-1), n(-1), n(-1, 4), p(1, 4), n(-1), l10(), n(2, 4),
      n(-4, 1, 8), l10(), n(2, 1, 2), n(1), n(2), n(2, 4), p(1, 4), n(-9), l10(), n(-2, 4);
  }

  std::cin.get();
  return 0;
}
