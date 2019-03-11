#pragma once

#include <functional>

#include "rng/rng.hpp"

namespace lcsc::mc {

template <typename U>
float hit_or_miss(rng<U>& engine, std::function<float(float)> f, float a,
                  float b, size_t n) {
    return 0.0f;
}

template <typename U>
float simple_sampling(rng<U>& engine, std::function<float(float)> f, float a,
                      float b, size_t n) {
    return 0.0f;
}

} // namespace lcsc::mc
