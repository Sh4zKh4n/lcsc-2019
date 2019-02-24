# Using external libraries

## Downloading TestU01

### Use CMake fork of TestU01 (recommended)

- Download a zipball from: <https://github.com/JamesHirschorn/TestU01-CMake>, and place it in `code/week4/ext/`.
- Unzip, and call the folder TestU01-CMake

### Manual

1. Download [TestU01](http://simul.iro.umontreal.ca/testu01/tu01.html) to an `ext/` (external) folder, and unzip.
2. Build the TestU01 library
   ```bash
   cd ext/TestU01-1.2.3
   ./configure --prefix=$PWD/../TestU01/
   make
   ```
   this will build, and install the library in `ext/TestU01/`.

## Using CMake to build against TestU01

Since TestU01 uses a different build system then CMake, we need to make CMake aware of it.

### Use CMake fork of TestU01

```cmake
# Add a TestU01 target
add_subdirectory("ext/TestU01-CMake")
target_include_directories(TestU01 PUBLIC "ext/TestU01-CMake/include")
```

### Manual

We will make a virtual target, that allows us to test our own RNGs with TestU01 through their C++ interface.

```cmake
# Add a TestU01 target
link_directories("ext/TestU01/lib")
add_library(TestU01 INTERFACE)
target_include_directories(TestU01 INTERFACE "ext/TestU01/include")
target_link_libraries(TestU01 INTERFACE mylib probdist testu01)
```

## Testing our RNG using TestU01

First, we must add a dependency of our LCSC library on TestU01. This way, any program that depends on LCSC will also depend on TestU01.

```cmake
target_link_libraries(lcsc INTERFACE TestU01)
```


We create a new file `example/test_rng.cpp`, and a target to our CMakeLists.txt:

```cmake
add_executable(test_rng "example/test_rng.cpp")
target_link_libraries(test_rng lcsc)
```

Now, calling make will build both `pring_rng` and `test_rng`, if their sources have been changed. If we want to specifically build one of the two, we can call for example: `make test_rng`.

TestU01 is a C library. You can include a C library in your C++ source code using:

```cpp
extern "C" {
#include "smarsa.h"
}
``` 

(As a side node, the reason C headers are treated differently is because of [name mangling](https://en.wikipedia.org/wiki/Name_mangling)).

Now on to testing our RNGs. We will test a Xorshift engine against the birthday paradox. Looking at the docs, we see that we need an _adapter_ for our RNG that allows it to be used with the TestU01 library. The interface for this (from the [TestU01 user guide](http://simul.iro.umontreal.ca/testu01/guideshorttestu01.pdf)) looks like:

```c
unif01_Gen *unif01_CreateExternGenBits (char *name,
unsigned int (*genB)(void));
```

Although usually C libraries are compatible with C++ code, we actually have a compatibility problem here with both arguments to this function (which, luckily, is quite rare).

The first argument expects a `char*` pointer, representing the name of the engine we want to test. String literals implicitly cast to `const char*` pointers in C++, and not to `char*`, while this does not happen in C. In particular, if we would call

```cpp
unif01_CreateExternGenBits("Xorshift", ...);
```

then this would not compile. Instead, we need to explicitely cast it to char*, which can be done using:
```cpp
unif01_CreateExternGenBits((char*)"Xorshift", ...);
```

The next argument is a function pointer. In this case, it is any function that does not take any arguments, and returns an unsigned integer. Unfortunately, the way that this library is set up forces us to use a global state. We do this by putting:

```cpp
auto seed = 1234512u;
auto engine = lcsc::xorshift<uint32_t>(13, 17, 5, seed);
```

outside of our `main` function, and using an anonymous function that calls `next` on this object:

```cpp
    auto gen = unif01_CreateExternGenBits((char*)"Xorshift-32",
                                          []() { return engine.next(); });
```

We will discuss anonymous functions in more detail in a future lecture.

## Updating your CMakeLists.txt

Last tutorial, we set up our CMake to build a header-only library. Here, I want to show you how to set up your build for the library when you have C++ source files as well.

In this case, I have only included one C++ file which contains a utility function for plotting a histogram. Again, I leave the correct implementation of this function up to you.

We will define a variable in CMake that contains a list of all our `.cpp` files:

```cmake
set(LIB_SOURCES
  "src/rng/util.cpp"
  # ... add other files here
)
```

We then add a _library_ target, since we want to compile the LCSC library. We do this using:

```cmake
add_library(lcsc ${LIB_SOURCES})
```

Finally, we replace `INTERFACE` (which is for header-only (virtual) libraries), with `PUBLIC`. This will ensure that any target that depends on the LCSC library uses the correct build flags and link against the correct libraries (such as TestU01). An alternative is to use the `PRIVATE` option. In this case, the statement will still affect the LCSC library itself, but not any target that depends on the LCSC library.
