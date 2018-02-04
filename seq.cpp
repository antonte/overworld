#include "seq.hpp"

Seq::N2::N2(Seq *seq, int note, int num) : seq(seq), note(note), num(num)
{
}

void Seq::N2::operator|(int den)
{
  played = true;
  seq->nn(note, num, den);
}

Seq::N2::~N2()
{
  if (!played)
    seq->nn(note, num);
}

Seq::N1::N1(Seq *seq, int note) : seq(seq), note(note)
{
}

Seq::N2 Seq::N1::operator>>(int num)
{
  played = true;
  return N2(seq, note, num);
}

Seq::N1::~N1()
{
  if (!played)
    seq->nn(note);
}

Seq::P1::P1(Seq *seq, int num) : seq(seq), num(num)
{
}

void Seq::P1::operator|(int den)
{
  played = true;
  seq->pp(num, den);
}

Seq::P1::~P1()
{
  if (!played)
    seq->pp(num);
}

Seq::Seq(Synth *synth) : synth(synth)
{
}

// note
Seq::N1 Seq::operator+(int note)
{
  return N1(this, note);
}

Seq::N1 Seq::operator-(int note)
{
  return N1(this, -note);
}

// delay
Seq::N2 Seq::operator>>(int num)
{
  return N2(this, 0, num);
}

// pause
Seq::P1 Seq::operator&(int num)
{
  return P1(this, num);
}

void Seq::operator*()
{
  nn();
}

void Seq::operator~()
{
  pp();
}

void Seq::key(int n)
{
  note = n;
  duration = 32;
}

void Seq::nn(int n, int num, int den)
{
  note += n;
  duration = duration * num / den;
  synth->play(note, duration);
}

void Seq::pp(int num, int den)
{
  duration = duration * num / den;
  synth->pause(duration);
}

int Seq::getNote() const
{
  return note;
}
