#include "audio.hpp"
#include "echo.hpp"
#include "amp.hpp"
#include "lpf.hpp"
#include "mix.hpp"
#include "saw.hpp"
#include "sdlpp.hpp"
#include "seq.hpp"
#include <iostream>

int main(int, char **)
{
  sdl::Init init(SDL_INIT_AUDIO);
  Audio audio;
  Amp amp(&audio, 1.3);
  Echo echo(&amp, 60 * sampleRate / 132 / 2, 0.2);
  Lpf lpf(&echo, 0.9);
  Mix mix(&lpf, 3);
  Saw sawN(mix.getInput(0));
  Seq n(&sawN);
  Saw sawM(mix.getInput(1));
  Seq m(&sawM);
  Saw sawB(mix.getInput(2));
  Seq b(&sawB);
  sawN.setTempo(132);
  sawM.setTempo(132);
  sawB.setTempo(132);
  // bar 1
  n.key(5);
  n+9; n-4>>3|4; n-5>>1|3; n-1>>2; n+1>>1|2; n+2>>5;

  m.key(5);
  m&4;

  b.key(5 - 24);
  b&4;
  for (int i = 0; i < 2; ++i)
  {
    // bar 2
    n.key(5);
    n+4>>1|2; n>>1|2; *n; n>>2; n>>1|2; *n; n+1>>2; n>>1|2; *n; n>>2; n>>1|2; *n;
    n-1>>2;   n>>1|2; *n; n>>2; n>>1|2; *n; n+1>>2; n>>3;

    m.key(5);
    m>>1|2; m>>1|2; *m; m>>2; m>>1|2; *m; m+2>>2; m>>1|2; *m; m-1>>2; m>>1|2; *m;
    m-1>>2; m>>1|2; *m; m>>2; m>>1|2; *m; m+2>>2; m-1>>3;

    b.key(5 - 24);
    *b;  b-3; b+5; b-7;
    b+5; b-3; b+5>>1|2; b-7>>3;

    // bar 4
    n.key(5);
    n+4;      n-4>>3|4; n-5>>1|3; n+2; n+3>>2; n>>3|2; n&1|3; n-3;
    n-2>>2;   n+5; *n; n+7; n-3>>3|2; n-2>>5|3;
    n+2>>4|5; n-4>>3|4; n-5>>1|3; n+2; n+3>>2; n>>3|2; n&1|3; n-3;
    n-2>>2;   n+5; n+5>>1|2; n-1; n-2; n-2; n>>8;

    m.key(5);
    m&4; ~m; ~m; ~m;

    b.key(5 - 24);
    *b;       b+4; b+1; b+1;
    b-2;      b-1; b-1>>1|2; b-5; b+2; b+1;
    b>>2;     b+4; b+1; b+1;
    b+1>>1|2; b-10; b+2; b+3; b-2; b-3; b+3>>2;

    // bar 8
    n.key(5);
    n+4;      n-4>>3|4; n-5>>1|3; n+2; n+3>>2; n>>3|2; n&1|3; n-3;
    n-2>>2;   n+5; *n; n+7; n-3>>3|2; n-2>>5|3;
    n+2>>4|5; n-4>>3|4; n-5>>1|3; n+2; n+3>>2; n>>3|2; n&1|3; n-3;
    n-2>>2;   n+5; n+5>>1|2; n-1; n-2; n-2; n>>8;

    m.key(5);
    m&4; ~m; ~m; ~m;

    b.key(5 - 24);
    *b;       b+4; b+1; b+1;
    b-2;      b-1; b-1>>1|2; b-5; b+2; b+1;
    b>>2;     b+4; b+1; b+1;
    b+1>>1|2; b-10; b+2; b+3; b-2; b-3; b+3; b-5;

    // bar 12
    n.key(5);
    n+4>>3|4; n-4; n-5>>2|3; n+9>>3|2; n-4>>5|3;
    n+3>>1|5; n-3; n-5>>2; n+8>>3|2; n-1>>9|3;
    n+2>>3|9; n-4; n-5>>2|3; n+9>>3|2; n-4>>5|3;
    n+3>>1|5; n-3; n-5>>2; n+12>>6;

    m.key(5);
    m&4; ~m; ~m; ~m;

    b.key(5 - 24);
    b+5>>1|2; b+1; b+1; b+2; b-2; b-3; b-4; b+4;
    b+1;      b+1; b+1; b+2; b+3; b-1; b-4; b-2;
    *b;       b-1; b+1; b+2; b+2; b+3; b-3; b-4;
    b+2;      b+2; b+3; b-5; b-2; b-1; b+1; b-5;

    // bar 16
    n.key(5);
    n+4;     n-4>>3|4; n-5>>1|3; n+2; n+3>>2; n>>3|2; n&1|3; n+2;
    n+2;     n-4; n-5>>2; n+2>>3|2; n+3>>8|3; n-3>>1|8;
    n+10>>2; n+2; n-2; n+2; n-2>>2; n-2>>1|4; n-1; n-2>>2;
    n-2>>4; ~n;

    m.key(5);
    m&4; ~m; ~m; ~m;

    b.key(5 - 24);
    *b; *b; b-2; *b;
    b-1; *b; b-1; *b;
    b+4; b&3;
    b+12>>1|3; b-5; b+5; *b;

    // bar 20
    n.key(5);
    n>>1|4;   n-3>>2; n+3>>3|2; n+2>>2|3; n+2>>1|2; n-1; n-1; n-1>>4; n&1|4;
    n-1;      n-3>>2; n+3>>3|2; n+2>>2|3; n+2>>4;
    n-4>>1|8; n-3>>2; n+3>>3|2; n+2>>2|3; n+2>>1|2; n+1; n+2; n+2>>4; n&1|4;
    n-9;      n-3>>2; n+3>>3|2; n+2>>2|3; n-2>>4;

    m.key(5);
    m-3>>1|4; m-4>>2; m+4>>3|2; m+2>>2|3; m+1>>1|2; m-1; *m; m-2>>4; m&1|4;
    *m;       m-4>>2; m+4>>3|2; m+2>>2|3; m+1>>4;
    m-3>>1|8; m-4>>2; m+4>>3|2; m+2>>2|3; m+1>>1|2; m+2; m+2; m+1>>4; m&1|4;
    m-8;      m-4>>2; m+4>>3|2; m+2>>2|3; m-4>>4;

    b.key(5 - 24);
    b>>1|2; b-3; b+3; b+4; b+1; b+2; b-2; b-3;
    b-2;    b-3; b+3; b+4; b+8; b-3; b-2; b-3;
    b-4;    b-3; b+3; b+4; b+3; b-2; b-1; b-2;
    b-2;    b-3; b+3; b+2; b-2; b-3; b+3>>2;
  }

  n.key(5);
  n&4;
  m.key(5);
  m&4;
  b.key(5 - 24);
  b&4;

  std::cin.get();
  return 0;
}
