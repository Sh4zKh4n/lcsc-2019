# Implementing a Monte Carlo module

## Adding another module to the LCSC library

Conceptually, our LCSC library consists of a number of modules. So far, we have been working on an `rng` module for generating random numbers. Now, we are going to add an additional `mc` module for Monte Carlo integration.

This week, we will start our Monte Carlo module by implementing _hit or miss_ and _simple sampling_ for 1D functions.

Compared to last week, this example code has the following _changes_:
- Add `include/mc/mc.hpp`
- Modify `include/lcsc.hpp` to contain `#include "mc/mc.hpp"`
- Add `example/test_monte_carlo.cpp`
- To keep this example code concise, I have removed TestU01, and the example applications.
- Modify `CMakeLists.txt` to use C++17 (for nested namespace definitions)

It is up to you to make similar adjustments to your own library, and to start
implementing basic Monte Carlo functionality.
