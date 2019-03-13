# Using CMake to build a library

## Header-only libraries

For our purposes, a translation unit in C++ is a source file (`.cpp`) that is
processed by the compiler.

In C++ we have the so-called ODR (one definition rule). An object such as a
function or a class can be /declared/ multiple times, e.g.

```cpp
void f();
class FooBar;
```

But classes and functions have at most one definition in the entire program:
```cpp
void f() {}
class FooBar {};
```

Templates are an exception to this. They can be defined at most once in each
translation unit, but they are allowed to be defined in multiple translation
units as long as the implementation is the same in each translation unit.
Although this may sound complicated, the main practical implication is that
templates (class templates and function templates) commonly have their
definitions in header files, and this header is included in multiple source
files. This ensures that the definition is the same in each translation unit.

A definition must be available in the same translation unit for each template
that is used (why do you think this is?), as opposed to non-template objects
which are allowed to be used as long as they are declared, and which later can
be found by the linker in different translation units. In other words: this does
not work:

```cpp
// main.cpp
template <typename T>
void f(T x);

int main() {
  f<int>(3);
}

// f.cpp
template <typename T>
void f(T x) { /* do something */ }
```

Libraries that rely heavily on templates, are typically header-only, meaning
that they consist solely of header files that are included by the user. The user
then compiles the library code as part of their translation units.

### Main library header

It is convenient to have one header that includes all other headers of your
library. I have defined a `lcsc.hpp` file that for now looks like:

```cpp
#include "rng/rng.hpp"
#include "rng/distribution.hpp"
```

This allows the user to either opt-in to specific functionality by including the appropriate header, or to include the entire library by using this main library header file.

## CMake

From the website:

    CMake is an open-source, cross-platform family of tools designed to build,
    test and package software. CMake is used to control the software compilation
    process using simple platform and compiler independent configuration files,
    and generate native makefiles and workspaces that can be used in the compiler
    environment of your choice.

We will use CMake to make our software builds reproducible on various systems.
The configuration file for CMake is called `CMakeLists.txt`. An example is added
in the current directory.

## Building software on top of the LCSC library

```bash
# we make a folder called 'build'
mkdir build
cd build
# run CMake, '..' means the CMakeLists.txt file is contained in the parent directory
cmake ..
# this will generate a Makefile, which can be used with make
make
# the binaries will be contained in the build directory
./print_rng
```
