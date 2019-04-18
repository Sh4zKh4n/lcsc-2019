# Writing a C++ library

For our purposes, a _software library_ is a collection of reusable code and
functionality. In the first part of the course, we are writing an RNG library,
which we will use later for a number of purposes (so we will be (re)using it
extensively!).

A software library is set up a bit differently from an ordinary program. I will
try to guide you through the main steps here.

## Header files

For now, we will split our program up into two parts:

1. An `rng` part, that implements the RNG engine
2. An _example_ program that will make use of the RNG functionality

We will do this with three files:

- `main.cpp`: this will contain a `main` function that has a number of calls to
  your RNG engine.
- `rng.cpp`: the main file that implements the random number generation
  functionality.
- `rng.hpp`: a header file, that defines the _interface_ to your RNG library.

The main reason that we require a header file, is because `main.cpp` and
`rng.cpp` are compiled independently (see the slides for week 1). However, in
`main.cpp` we want to use functions that are defined in `rng.cpp`. For now, you
can view the header `rng.hpp` as a file that tells `main.cpp` which
functionality is defined in `rng.cpp` and how to call upon this functionality
(functions, classes and so on).

## `#pragma once`

A header file typically starts with `#pragma once`. This ensures that the header
file is only read once by the compiler, even if it is included multiple times.
This typically happens because header files can also include each other.

Although this is non-standard C++, every compiler supports this extension and it
is better than any alternative way to avoid redefinitions.

## Fixed width integers

Because our RNGs exploit the binary nature of integers on computers, we want to
ensure that the integers we are using have a specific number of bits, and are
stored either as signed or unsigned integers. In C++, `int` has no guaranteed
width (on modern systems it is typically 32 bits).

One way to ensure that the integers we use have a specific width and signedness,
is by using a support library from the C standard library. C standard libraries
can be imported into C++ using `#include <c[name_of_lib]>`. These are C++
compatible versions of the original C libraries, which can also be imported (but
you should not do this) using `#include <[name_of_lib].h>`.

```cpp
#include <cstdint>

uint32_t x;
int64_t y;
// ...
```
  
See: <https://en.cppreference.com/w/cpp/header/cstdint> for more details.

In my example code, I have used a type alias for 64-bit unsigned integers:

```cpp
using T = uint64_t;
// from now on T is an alias for 64-bit unsigned integers...
T x = 0u;
```

In our RNG library, we want to keep the type that is used flexible, depending on
the LCRNG parameters. We will discuss how to do this generalically when we get
to _templates_.

## Putting everything together

I have implemented some of the code from the lecture slides in the three files:
`main.cpp`, `rng.hpp` and `rng.cpp`. You can compile this code with:

```bash
g++ main.cpp rng.cpp -o week2
```

Note that we do not compile `rng.hpp`, it is already part of (both) `main.cpp`
and `rng.cpp`! This is done using an `#include "rng.hpp"` statement.

Let us quickly recap how this compilation works. Look at the content of the file
`rng.hpp`, it does not include any actual implementations. It only contains
definitions for classes and function signatures. The implementations are found
in `rng.cpp`.

When `main.cpp`, is compiled, the compiler knows that there is a class
`lcsc::lcrng` since this is declared by `rng.hpp`, but it does not know how the
specific implementation of the member functions. Only when `rng.cpp` is compiled, the
member function implementations are available. The linker will then fill in the
missing references to the implementations of the functionality exposed by
`rng.hpp` to `main.cpp`.
