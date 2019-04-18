#include "rng.hpp"

namespace lcsc {

lcrng::lcrng(T a, T c, T m, T seed) : a_(a), c_(c), m_(m), x_(seed) {}

T lcrng::next() { return 0; }

} // namespace lcsc
