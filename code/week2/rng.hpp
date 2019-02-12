#pragma once

// this header defines integers with a specific number of bits
#include <cstdint>

namespace lcsc {

// for this demo, use 64 bit unsigned integers everywhere
using T = uint64_t;

class rng {
  public:
    virtual T next() = 0;
};

class lcrng : public rng {
  public:
    lcrng(T a, T c, T m, T seed);

    T next() override;

  private:
    T a_;
    T c_;
    T m_;
    T x_;
};

} // namespace lcsc
