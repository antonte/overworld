#include "mix.hpp"
#include "const.hpp"
#include <algorithm>

Mix::Input::Input(Mix *mix) : mix(mix)
{
}

void Mix::Input::queue(int16_t *b, size_t size)
{
  buff.insert(std::end(buff), b, b + size);
  mix->process();
}

Mix::Mix(Sink *sink, int inputNum) : sink(sink)
{
  while (static_cast<int>(inputs.size()) < inputNum)
    inputs.emplace_back(this);
}

Mix::Input *Mix::getInput(int idx)
{
  return &inputs[idx];
}

void Mix::process()
{
  auto min = std::min_element(std::begin(inputs), std::end(inputs), [](Input &x, Input &y) {
    return x.buff.size() < y.buff.size();
  });

  auto sz = min->buff.size();
  if (sz > 0)
  {
    std::vector<int16_t> b;
    b.resize(sz);
    std::fill(std::begin(b), std::end(b), 0);
    for (auto &input : inputs)
    {
      auto in = std::begin(input.buff);
      for (auto out = std::begin(b); out != std::end(b); ++out, ++in)
        *out += *in;
      input.buff.erase(std::begin(input.buff), std::begin(input.buff) + sz);
    }
    sink->queue(b.data(), sz);
  }
}
