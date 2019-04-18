#include <iostream>

#include "rng.hpp"

int main() {
    auto seed = 12345u;
    auto park_miller = lcsc::lcrng(16807, 0, (1u << 31) - 1, seed);
    for (int i = 0; i < 10; ++i) {
        std::cout << park_miller.next() << "\n";
    }

    return 0;
}
