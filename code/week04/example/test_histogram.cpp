#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "lcsc.hpp"

int main() {
    auto seed = 1234512u;
    auto engine = lcsc::xorshift<uint32_t>(13, 17, 5, seed);

    auto n = 10u;
    auto xs = std::vector<uint32_t>(n);
    std::generate(xs.begin(), xs.end(), [&]() { return engine.next(); });

    lcsc::histogram(xs, 5);

    return 0;
}
