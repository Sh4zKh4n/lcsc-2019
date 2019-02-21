#include <cstdint>
#include <iostream>

#include "lcsc.hpp"

int main() {
    // set the seed to some arbitrary unsigned number (notice the 'u' suffix to
    // make it unsigned)
    auto seed = 1234512u;

    // initialize a Xorshift engine, with parameters that give full period
    auto engine = lcsc::xorshift<uint32_t>(13, 17, 5, seed);

    // initialize a sampler that generates random floats in the interval
    // [1.0, 5.0]
    auto sampler =
        lcsc::uniform_distribution<float, uint32_t>(1.0f, 5.0f, engine);

    // output the first 10 random integers
    for (int i = 0; i < 10; ++i) {
        std::cout << engine.next() << "\n";
    }

    // output the first 10 uniformly sampled reals
    for (int i = 0; i < 10; ++i) {
        std::cout << sampler.sample() << "\n";
    }

    // indicate that the program ran correctly
    return 0;
}
