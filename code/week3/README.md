# Using CMake to build a library

## Header-only libraries

- One definition rule
- Templates
- Pros and cons

### Main library header

It is convenient to have one header that includes all other headers of your
library.

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
# run CMake, '..' means the CMakeLists.txt
file is contained in the parent directory
cmake ..
# this will generate a Makefile, which can be used with make
make
# the binaries will be contained in the build directory
./print_rng
```
