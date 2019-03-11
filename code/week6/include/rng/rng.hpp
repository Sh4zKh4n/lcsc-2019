#pragma once

namespace lcsc {

/**
 * An `rng` is capable of generating uniformly distributed integers in some set
 * $$M = { 0, ..., m - 1 }$$
 *
 * To distinguish an rng from a distribution, we call them random number
 * generator _engines_.
 *
 * Here, we define an RNG as a template, so that we define an interface
 * regardless of the width (number of bits) of the integers that are generated.
 *
 * The template parameter U should be an unsigned integer type.
 */
template <typename U>
class rng {
  public:
    /** Generate the next random integer. */
    virtual U next() = 0;

    /** The size of the set $M$, i.e. $m$. */
    virtual U max() = 0;
};

/**
 * An LCRNG is an RNG that uses a generator function of the form:
 * $$f(x_i) = (a * x_{i - 1} + c) mod m$$
 */
template <typename U>
class lcrng : public rng<U> {
  public:
    /** Construct the LCRNG with the given parameters and seed. */
    lcrng(U a, U c, U m, U seed) : a_(a), c_(c), m_(m), x_(seed) {}

    U next() override {
        x_ = (a_ * x_ + c_) % m_;
        return x_;
    }

    U max() override { return m_; }

  protected:
    U a_;
    U c_;
    U m_;
    U x_;
};

/** Park Miller is an LCRNG with decent statistical behaviour.  */
class park_miller : public lcrng<uint32_t> {
  public:
    park_miller(uint32_t seed) : lcrng(16807, 0, (1u << 31) - 1, seed) {}

    uint32_t next() override {
        // TODO use Shrage's trick
        x_ = (a_ * x_ + c_) % m_;
        return x_;
    }
};

/**
 * A Xorshift engine is an RNG that uses a linear generator function of the
 * form:
 * $$T = (Id + L^a)(Id + R^b)(Id + L^a),$$
 * where L and R are the left and right bitshift operators.
 */
template <typename U>
class xorshift : public rng<U> {
  public:
    /** Construct the Xorshift engine with the given parameters and seed. */
    xorshift(U a, U b, U c, U seed) : a_(a), b_(b), c_(c), x_(seed) {}

    U next() override {
        x_ ^= x_ << a_;
        x_ ^= x_ >> b_;
        x_ ^= x_ << c_;
        return x_;
    }

    U max() override { return ~((U)0); }

  private:
    U a_;
    U b_;
    U c_;
    U x_;
};

} // namespace lcsc
