#include "audio.hpp"
#include "const.hpp"

namespace
{
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

  SDL_AudioSpec obtained;
}

Audio::Audio() : audio(nullptr, false, desired(), &obtained, 0)
{
  audio.pause(false);
}

void Audio::queue(int16_t *buff, size_t size)
{
  audio.queue(buff, size * sizeof(int16_t));
}
