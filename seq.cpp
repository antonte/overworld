#include "seq.hpp"

Seq::N2::N2(Seq *seq, int note, int num) : seq(seq), note(note), num(num)
{
}

void Seq::N2::operator|(int den)
{
  played = true;
  seq->setNote(note, num, den);
}

Seq::N2::~N2()
{
  if (!played)
    seq->setNote(note, num);
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
    seq->setNote(note);
}

Seq::P1::P1(Seq *seq, int num) : seq(seq), num(num)
{
}

void Seq::P1::operator|(int den)
{
  played = true;
  seq->pause(num, den);
}

Seq::P1::~P1()
{
  if (!played)
    seq->pause(num);
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
  setNote();
}

void Seq::operator~()
{
  pause();
}

void Seq::key(int n)
{
  note = n;
  duration = 32;
}

void Seq::setNote(int n, int num, int den)
{
  note += n;
  duration = duration * num / den;
  synth->play(note, duration);
}

void Seq::pause(int num, int den)
{
  duration = duration * num / den;
  synth->pause(duration);
}

int Seq::getNote() const
{
  return note;
}
