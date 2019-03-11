#include <cmath>
#include <cstdint>
#include <iostream>

#include "lcsc.hpp"

int main() {
    auto seed = 1234512u;
    auto engine = lcsc::xorshift<uint32_t>(13, 17, 5, seed);

    auto f = [](float x) { return std::sqrt(1.0f - x * x); };

    std::cout << "Hit or miss: "
              << lcsc::mc::hit_or_miss(engine, f, 0.0f, 1.0f, 10) << "\n";
    std::cout << "Simple sampling: "
              << lcsc::mc::simple_sampling(engine, f, 0.0f, 1.0f, 10) << "\n";

    return 0;
}
