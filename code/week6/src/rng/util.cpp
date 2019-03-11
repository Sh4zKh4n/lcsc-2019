#include <iostream>

#include "rng/util.hpp"

namespace lcsc {

void histogram(const std::vector<uint32_t>& xs, int bin_count) {
    auto bins = std::vector<uint32_t>(bin_count);
    // TODO fill bins with xs
    // ... here we just use a constant 10
    std::fill(bins.begin(), bins.end(), 10);

    // Output a (horizontal) histogram
    auto i = 0u;
    for (auto& bin : bins) {
      std::cout << i++ << ": " << std::string(bin, '*') << "\n";
    }
}

} // namespace lcsc
