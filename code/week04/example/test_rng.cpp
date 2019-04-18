#include <cstdint>
#include <functional>
#include <iostream>

#include "lcsc.hpp"

extern "C" {
#include "smarsa.h"
}

constexpr auto seed = 1234512u;
auto engine = lcsc::xorshift<uint32_t>(13, 17, 5, seed);

int main() {
    auto gen = unif01_CreateExternGenBits((char*)"Xorshift-32",
                                          []() { return engine.next(); });

    smarsa_BirthdaySpacings(gen, NULL, 1, 1000, 0, 10000, 2, 1);
    smarsa_BirthdaySpacings(gen, NULL, 1, 10000, 0, 1000000, 2, 1);

    unif01_DeleteExternGenBits(gen);

    return 0;
}
