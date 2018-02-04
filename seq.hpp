#pragma once
#include "synth.hpp"
#include "const.hpp"

class Seq
{
public:
  struct N2
  {
    N2(Seq *seq, int note, int num);
    Seq *seq;
    int note;
    int num;
    bool played = false;
    void operator|(int den);
    ~N2();
  };

  struct N1
  {
    N1(Seq *seq, int note);
    Seq *seq;
    int note;
    bool played = false;

    N2 operator>>(int num);
    ~N1();
  };

  struct P1
  {
    P1(Seq *seq, int num);
    Seq *seq;
    int num;
    bool played = false;
    void operator|(int den);
    ~P1();
  };
  Seq(Synth *synth);

  // note
  N1 operator+(int note);
  N1 operator-(int note);

  // delay
  N2 operator>>(int num);

  // pause
  P1 operator&(int num);
  void operator*();
  void operator~();
  void key(int n);

  int getNote() const;

private:
  int note = 0;
  int duration = quarter;
  void nn(int n = 0, int num = 1, int den = 1);
  void pp(int num = 1, int den = 1);
  Synth *synth;
};
